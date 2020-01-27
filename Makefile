SRC = init_mlx.c main.c vector3d.c render.c intersection.c \
		figure.c get_color.c get_parametr.c get_vector.c \
		get_type.c light.c parse_file.c parse_marks.c parsing_func.c \
		read_file.c validation_main.c camera.c normals_to_figures.c calculate_light.c \
		prepare_figures.c get_normal.c
OBJ = $(SRC:.c=.o)
HDR = rtv1.h
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
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all