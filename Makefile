SRC = init_mlx.c main.c vector3d.c render.c intersection.c \
		figure.c get_color.c get_parametr.c get_vector.c \
		get_type.c light.c parse_file.c parse_marks.c parsing_func.c \
		read_file.c validation_main.c camera.c normals_to_figures.c calculate_light.c \
		prepare_figures.c

OBJ_DIR = ./objects
SRC_DIR = ./src
HDR_DIR = ./includes
LIBFT_HDR_DIR = ./libft
MLX_HDR_DIR = ./mlx
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
#OBJ = $(SRC:.c=.o)
HDR = ./includes/rtv1.h ./includes/validation.h ./libft/libft.h ./mlx/mlx.h
LIB = libft/libft.a
MLX = mlx/lmlx.a
NAME = RTv1

all: $(NAME)

# %.o: src/%.c $(HDR)
# 	gcc -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	gcc  -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) -o $@ -c $<

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

$(NAME): $(OBJ_DIR) libs $(OBJ)
	#gcc -Wall -Wextra -Werror -o $(NAME) -I $(HDR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit
	@echo "test1"
	gcc -Wall -Wextra -Werror -o $(NAME) -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)