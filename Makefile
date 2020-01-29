SRC = init_mlx.c main.c vector3d.c render.c intersection.c \
		figure.c get_color.c get_parametr.c get_vector.c \
		get_type.c light.c parse_file.c parse_marks.c parsing_func.c \
		read_file.c validation_main.c camera.c normals_to_figures.c calculate_light.c \
		prepare_figures.c

OBJ_DIR = ./objects
SRC_DIR = ./src
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
#OBJ = $(SRC:.c=.o)
HDR = rtv1.h
LIB = libft/libft.a
MLX = mlx/lmlx.a
NAME = RTv1

all: $(NAME)

$(NAME): $(OBJ_DIR) libs $(OBJ)
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HDR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit

# %.o: src/%.c $(HDR)
# 	gcc -c $<

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(HDR)
	gcc -o $@ -c $<

libs:
	make -C ./libft
clean:
	make clean -C ./libft
	rm -rf $(OBJ)
	rm -rf $(OBJ_DIR)
fclean: clean
	make fclean -C ./libft
	rm -rf $(NAME)
re: fclean all

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)