*This project has been created as part of the 42 curriculum by zscekic.*

## Description

**Codexion** is a concurrency simulation written in C with POSIX threads.

Several coders sit around a circular table with a shared quantum compiler in the
middle. Between every two coders lies one USB dongle, so there are as many
dongles as coders. To **compile**, a coder needs both dongles next to them
(left and right). After compiling, the coder puts both dongles back, **debugs**,
then **refactors**, and then tries to compile again. A coder who does not start
compiling within `time_to_burnout` ms of the start of their last compile
**burns out**, and the simulation stops.

The project is about sharing limited resources safely between threads:

- every coder is a thread, and every dongle is protected by its own mutex;
- a released dongle cannot be taken again before a **cooldown** has passed;
- when several coders want the same dongle, the dongle decides who gets it with
  a **scheduler**: `fifo` (first come, first served) or `edf` (earliest
  burnout deadline first), implemented with a hand-written **min-heap**;
- a separate **monitor** thread detects burnout within 10 ms and stops the
  simulation, or stops it when every coder has compiled enough times;
- the program must be free of data races, deadlocks, interleaved log lines and
  memory leaks.

### Project layout

| File | Role |
|---|---|
| `include/codexion.h` | all structs, the mutex map, prototypes |
| `src/main.c` | parse, init, run threads, join, cleanup |
| `src/parsing.c` | argument validation |
| `src/init.c`, `src/init_sync.c` | allocation, seating, mutex / cond creation |
| `src/cleanup.c` | destroys only what was created, frees everything |
| `src/threads.c` | creates and joins coder threads and the monitor |
| `src/coder.c`, `src/coder_actions.c` | the coder loop: take, compile, release, debug, refactor |
| `src/dongle.c`, `src/dongle_wait.c` | requesting, waiting for and releasing dongles, cooldown |
| `src/heap.c`, `src/heap_utils.c` | the priority queue (min-heap) |
| `src/scheduler.c` | the `fifo` / `edf` comparison |
| `src/monitor.c` | burnout and "everyone is done" detection |
| `src/log.c`, `src/state.c`, `src/state_coder.c`, `src/time.c` | serialized logs, locked getters / setters, time helpers |

## Instructions

### Compile

```bash
make        # builds ./codexion with cc -Wall -Wextra -Werror -pthread
make clean  # removes object files
make fclean # removes object files and the binary
make re     # fclean + all
```

### Run

```bash
./codexion number_of_coders time_to_burnout time_to_compile time_to_debug \
           time_to_refactor number_of_compiles_required dongle_cooldown scheduler
```

- All times are in milliseconds.
- `scheduler` is `fifo` or `edf`.
- All 8 arguments are mandatory. Negative numbers, non-integers, values above
  `INT_MAX`, 0 coders, 0 required compiles or an unknown scheduler are rejected
  with an error message and exit code 1.

### Output

Every state change is printed as `timestamp_in_ms coder_id message`:

```
0 1 has taken a dongle
0 1 has taken a dongle
0 1 is compiling
200 1 is debugging
400 1 is refactoring
...
800 3 burned out
```

### Examples

```bash
./codexion 1 800 200 200 200 10 0 fifo      # one dongle only: burns out at ~800
./codexion 5 2000 200 200 200 10 0 fifo     # no burnout, stops after 10 compiles each
./codexion 5 2000 200 200 200 7 0 edf       # same with edf
./codexion 5 500 200 200 200 10 0 fifo      # burns out at ~500
./codexion 5 3000 200 200 200 10 400 fifo   # cooldown 400, no burnout
./codexion 5 3000 200 200 200 10 800 edf    # heavy contention: compare with fifo
```

### Checking threads and memory (Linux)

```bash
valgrind --leak-check=full ./codexion 5 2000 200 200 200 3 0 fifo
valgrind --tool=helgrind   ./codexion 5 2000 200 200 200 3 0 fifo
valgrind --tool=drd        ./codexion 5 2000 200 200 200 3 0 edf
```

Under valgrind everything runs many times slower, so a burnout during these
runs is expected. Only the `ERROR SUMMARY` matters.

## Blocking cases handled

### Deadlock (Coffman's conditions)

A deadlock needs all four Coffman conditions at the same time: mutual
exclusion, hold and wait, no preemption and circular wait. Codexion breaks two
of them.

- **Hold and wait is broken.** A coder never holds one dongle while waiting for
  the other. `take_both` puts a request in **both** dongle queues, waits while
  holding no dongle, and takes both dongles together, in one step under both
  dongle mutexes, only when both are available.
- **Circular wait is broken for the mutexes.** When a coder locks two dongle
  mutexes at the same time, it always locks the dongle with the **lower index
  first** (`first`, then `second`, fixed in `link_coder`). Every thread uses the
  same global order, so no cycle of threads waiting for each other's mutex can
  form.
- **A single global lock order** is used everywhere else too:
  `print_mutex → stop_mutex`, and `dongle mutex → coder mutex / stop_mutex`.
  No code path takes them in reverse.

### Starvation and fairness

- Every dongle has a **priority queue** of requests. A coder may only take a
  dongle when its own request is at the top of that dongle's queue.
- **FIFO:** the request with the smaller ticket (earlier arrival) goes first.
- **EDF:** the request with the earlier deadline
  (`last_compile_start + time_to_burnout`) goes first. Equal deadlines are
  broken by the ticket, so the order is always fully deterministic.
- **One ticket per request.** The same ticket (request time in microseconds,
  ×1000 + coder id, so two tickets are never equal) is put in both queues. The
  waiting coders are therefore in the same order on every dongle, and the coder
  with the best ticket is first in both of its queues, so somebody can always
  make progress.
- **No waiting chains.** Because nobody holds a dongle while waiting, one slow
  coder cannot block a whole line of neighbours. This is what lets
  `5 3000 200 200 200 10 400` finish without a burnout.
- **Odd coders start first.** Even-numbered coders wait 10 ms before their
  first request, so coders 1, 3, … compile together at the start instead of
  lining up one behind the other.

### Cooldown

- When a dongle is released, `released_at` is set to the current time. The
  dongle is "my turn" only if `now >= released_at + dongle_cooldown`.
- The end of a cooldown is not an event: no thread rings a bell when it ends.
  A coder waiting for a dongle that is free but still cooling down therefore
  uses `pthread_cond_timedwait` with an absolute wake-up time
  (`released_at + cooldown`), so it wakes exactly when the cooldown is over.
  If the dongle is held by someone, it uses `pthread_cond_wait` and is woken by
  the release.

### Precise burnout detection

- The monitor thread checks every coder about every **1 ms**:
  `now - last_compile_start >= time_to_burnout` means burnout.
- `last_compile_start` is read through a locked getter, because the coder thread
  writes it at the same time.
- On burnout, `log_burnout` sets the stop flag **and** prints the line while
  holding `print_mutex`, so the message appears within about 1 ms of the real
  burnout (the subject allows 10 ms) and **no line can be printed after it**.
- The monitor also stops the simulation when every coder has compiled at least
  `number_of_compiles_required` times.

### Clean stop (no thread left sleeping)

- After setting the stop flag, the monitor calls `wake_all`: it locks every
  dongle mutex and broadcasts its condition variable. Coders asleep in
  `cond_wait` wake up, see the stop flag and leave their loop.
- Coders in the middle of a sleep use `precise_sleep`, which checks the stop
  flag every 0.5 ms and returns early.
- `main` joins every thread **before** `cleanup` destroys mutexes and frees
  memory, so no thread can touch freed memory.

### Single coder

With one coder there is only one dongle on the table. The coder takes it, logs
it once, and waits on the dongle's condition variable until the monitor stops
the simulation. They can never compile, so they burn out at `time_to_burnout`.

### Log serialization

Every log line is printed while holding `print_mutex`, so two messages can
never be mixed on one line. Inside the lock the stop flag is checked first, so
nothing is printed once the simulation is over. Timestamps are taken inside the
lock, so they always appear in increasing order.

### Partial failure during setup

If a `malloc`, `pthread_mutex_init`, `pthread_cond_init` or `pthread_create`
fails, the program cleans up only what was really created: memory is zeroed
right after allocation, and the `sync_*` counters record how many mutexes and
condition variables exist. If not every thread could be started, the threads
that did start are stopped, woken and joined before cleanup.

## Thread synchronization mechanisms

### Threads

- **One thread per coder** (`pthread_create` with `coder_routine`; each coder
  receives a pointer to its own `t_coder`).
- **One monitor thread** (`monitor_routine`, which receives the whole `t_sim`).
- The **main thread** creates them, then waits for all of them with
  `pthread_join`.

### Mutexes (`pthread_mutex_t`): who protects what

| Mutex | Protects |
|---|---|
| `sim->stop_mutex` | `sim->stopped` |
| `sim->print_mutex` | standard output (one log line at a time) |
| `coder->mutex` | `last_compile`, `compile_count` of that coder |
| `dongle->mutex` | `holder`, `released_at` and the request queue of that dongle |

Data that is written before the threads start and only read afterwards
(parameters, start time, coder ids, dongle pointers) needs no lock.

### Condition variables (`pthread_cond_t`)

Each dongle has one condition variable, used together with its mutex as a
waiting room:

- a coder that cannot take a dongle sleeps on **the condition variable of the
  dongle that blocks it**: `pthread_cond_wait` if someone holds it,
  `pthread_cond_timedwait` if it is free but cooling down;
- `pthread_cond_wait` releases the mutex while sleeping and takes it back
  before returning, so other threads can change the dongle meanwhile;
- every wait is inside a `while` loop that re-checks the condition, because a
  thread can wake up and find that it is still not its turn;
- releasing a dongle uses `pthread_cond_broadcast` (not `signal`) under the
  dongle mutex, because the stop must reach every waiter and because the
  sleeper that `signal` would pick might not be the coder whose turn it is.
  Broadcasting while holding the mutex prevents a lost wake-up between a
  waiter's check and its sleep.

### How race conditions are prevented: examples

- **Taking a dongle.** Checking "is it free, cooled down, and am I first in its
  queue?" and then setting `holder` both happen under the dongle mutex (for both
  dongles at once). No other coder can take the same dongle in between, so a
  dongle is never held by two coders.
- **Coder ↔ monitor.** The coder writes `last_compile` and `compile_count` and
  the monitor reads them at the same time. Both sides go through getters and
  setters that lock `coder->mutex`, copy the value, and unlock. The monitor
  never reads a half-written value.
- **Monitor → coders (stop).** `stopped` is only read and written through
  `is_stopped` / `set_stopped` under `stop_mutex`. Coders check it in their
  loop, in every wait loop, in `precise_sleep` and before printing.
- **Logging.** `print_mutex` serializes `printf`. The stop check happens inside
  the same lock, which removes the race between "burned out" and a last
  message from another coder.
- **Results read after a lock is released.** `take_both` stores the result of
  the wait in a local variable before unlocking, instead of reading the shared
  `holder` field after unlocking.

## Resources

- POSIX threads: `man pthread_create`, `man pthread_mutex_lock`,
  `man pthread_cond_wait`, `man pthread_cond_timedwait`, and the overview at
  <https://man7.org/linux/man-pages/man7/pthreads.7.html>.
- *Operating Systems: Three Easy Pieces* (Arpaci-Dusseau), chapters on locks,
  condition variables and common concurrency problems:
  <https://pages.cs.wisc.edu/~remzi/OSTEP/>.
- E. G. Coffman, M. Elphick, A. Shoshani, *System Deadlocks*, ACM Computing
  Surveys, 1971: the four conditions for deadlock.
- The dining philosophers problem (E. W. Dijkstra), which Codexion is based on:
  <https://en.wikipedia.org/wiki/Dining_philosophers_problem>.
- Binary heaps / priority queues: Cormen et al., *Introduction to Algorithms*,
  chapter 6 (Heapsort).
- C. L. Liu, J. W. Layland, *Scheduling Algorithms for Multiprogramming in a
  Hard-Real-Time Environment*, 1973: earliest deadline first.
- Valgrind's Helgrind and DRD manuals:
  <https://valgrind.org/docs/manual/hg-manual.html>,
  <https://valgrind.org/docs/manual/drd-manual.html>.

### How AI was used

I used Claude (Anthropic) as a tutor and pair programmer throughout the project:

- **Explaining concepts:** mutexes, condition variables, lost wake-ups,
  Coffman's conditions, heaps, FIFO / EDF, `pthread_cond_timedwait`, with
  diagrams and check questions.
- **Debugging and design:** analysing the logs of test runs. In particular, the
  AI found that the first "take the first dongle, then the second" approach
  created waiting chains under cooldown, and proposed the "take both dongles
  together with one ticket" design, which we tested before using it.
- **Testing:** test scripts for the evaluation cases, a log checker for
  cooldown and dongle duplication, and failure-injection tests for cleanup.
- **Documentation:** study notes, and a first draft of this README, which I
  reviewed.
