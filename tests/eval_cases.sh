#!/bin/bash
# Benchmark cases from the evaluation sheet. Run from repo root after `make`.
BIN=./codexion

echo "== Easy: must burn out ~800";            $BIN 1 800 200 200 200 10 0 fifo | tail -n 3
echo "== Easy: no burnout, 10 compiles each";   $BIN 5 2000 200 200 200 10 0 fifo | tail -n 3
echo "== Easy: no burnout, 7 compiles (edf)";   $BIN 5 2000 200 200 200 7 0 edf | tail -n 3
echo "== Less easy: must burn out ~500 (last line)"; $BIN 5 500 200 200 200 10 0 fifo | tail -n 3
echo "== Medium: cooldown 400";                 $BIN 5 3000 200 200 200 10 400 fifo | tail -n 3
echo "== Medium: fifo vs edf, cooldown 800"
$BIN 5 3000 200 200 200 10 800 fifo > /tmp/codexion_fifo.log
$BIN 5 3000 200 200 200 10 800 edf  > /tmp/codexion_edf.log
echo "   compare /tmp/codexion_fifo.log and /tmp/codexion_edf.log"

# Thread checks (also done during evaluation):
#   valgrind --tool=helgrind ./codexion 5 2000 200 200 200 3 0 fifo
#   valgrind --tool=drd      ./codexion 5 2000 200 200 200 3 0 edf
#   make re CFLAGS="-Wall -Wextra -Werror -pthread -fsanitize=thread -g"
