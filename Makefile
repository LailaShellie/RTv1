SRC = init_mlx.c main.c vector3d.c
OBJ = $(SRC:.c=.o)
HDR = rtv1.h
VAL = src/validation/validation.a
LIB = libft/libft.a
MLX = mlx/lmlx.a
NAME = RTv1

all: $(NAME)

$(NAME): libs $(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HDR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit
%.o: src/%.c $(HDR)
	gcc -c $<
libs:
	make -C ./libft
	make -C ./src/validation
clean:
	make clean -C ./libft
	make clean -C ./src/validation
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	make fclean -C ./src/validation
	rm -rf $(NAME)
re: fclean all