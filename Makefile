NAME = fdf

SRCS = src/draw.c  src/get_next_line.c  src/get_next_line_utils.c  src/main.c  src/map_reader.c  src/map_utils.c  src/utils.c  src/utils_split.c  src/utils_str.c  src/window.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lminilibx-linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx-linux 
	cc $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iminilibx-linux -c $< -o $@

clean:
	make -C ./minilibx-linux clean
	rm -f $(OBJS)

fclean: clean
	make -C ./minilibx-linux clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re