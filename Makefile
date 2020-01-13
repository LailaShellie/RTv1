SRC = init_mlx.c main.c read_file.c parse_file.c parsing_func.c get_cam.c
OBJ = $(SRC:.c=.o)
HDR = rtv1.h
LIB = libft/libft.a
MLX = mlx/lmlx.a
NAME = RTv1

all: $(NAME)

$(NAME): $(LIB) $(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HDR) $(LIB) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit
%.o: src/%.c $(HDR)
	gcc -c $<
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all