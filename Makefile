CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -g3
INCLUDE =
LIB =
L_FLAGS = -lraylib -lGL -lm -lpthread -lrt -lX11
MAKEFLAGS += -j

NAME = ray

HEADERS := \
	includes/engine.h \

SRCS := \
	srcs/main.c \
	srcs/engine.c \

OBJS = $(SRCS:%.c=%.o)

%.o: %.c Makefile $(HEADERS)
	$(CC) $(CC_FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) $(INCLUDE) $(LIB) $(L_FLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf srcs/*.o

fclean: clean
	rm -rf $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re