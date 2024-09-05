CC = gcc
CC_FLAGS = -Wall -Wextra -Werror -g3
INCLUDE = -I./libft
LIB = -L./libft
L_FLAGS = -lraylib -lGL -lm -lpthread -lrt -lX11 -lft
MAKEFLAGS += -j

NAME = ray

HEADERS := \
	includes/engine.h \
	includes/camera.h \
	includes/ray.h \
	includes/vec3.h \
	includes/color.h \
	includes/sphere.h \
	includes/scene.h \
	includes/utils.h \
	includes/multi_threading.h \
	includes/stb_image_write.h \

SRCS := \
	srcs/main.c \
	srcs/engine.c \
	srcs/camera.c \
	srcs/vec3.c \
	srcs/color.c \
	srcs/ray.c \
	srcs/sphere.c \
	srcs/scene.c \
	srcs/utils.c \
	srcs/multi_threading.c \

OBJS = $(SRCS:%.c=%.o)

%.o: %.c Makefile $(HEADERS)
	$(CC) $(CC_FLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(MAKE) -C ./libft
	$(CC) $(CC_FLAGS) $(OBJS) $(INCLUDE) $(LIB) $(L_FLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -rf srcs/*.o

fclean: clean
	$(MAKE) -C ./libft fclean
	rm -rf $(NAME)

re: fclean
	$(MAKE)

.PHONY: all clean fclean re