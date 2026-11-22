NAME		= codexion

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -pthread
INCLUDES	= -I include

SRC_DIR		= src
OBJ_DIR		= obj

SRCS		= main.c \
			  parsing.c \
			  init.c \
			  init_sync.c \
			  threads.c \
			  cleanup.c \
			  time.c \
			  log.c \
			  state.c \
			  state_coder.c \
			  heap.c \
			  heap_utils.c \
			  scheduler.c \
			  dongle.c \
			  dongle_wait.c \
			  coder.c \
			  coder_actions.c \
			  monitor.c

OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADER		= include/codexion.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
