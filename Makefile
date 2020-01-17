SRC = init_mlx.c main.c read_file.c parse_file.c \
	parsing_func.c parse_marks.c get_parametr.c \
	get_point_or_vector.c get_type.c light.c figure.c get_color.c
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
$(LIB):
	make -C ./libft
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all