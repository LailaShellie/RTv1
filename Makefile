SRC = init_mlx.c main.c objects.c vector3d_1.c vector3d_2.c render.c intersection.c \
		diffusive_light.c calculate_light.c \
		prepare_figures.c get_normal.c specular_light.c \
		parse_json_goto.c parse_json_read_param.c parse_json.c \
		print_data.c parse_json_getdata.c parse_json_data_params.c \
		parse_json_name_value.c \
		parse_json_2nd_level.c parse_json_3rd_level.c \
		test_rotation_matrix.c free_rtv1.c

OBJ_DIR = ./objects
SRC_DIR = ./src
HDR_DIR = ./includes
LIBFT_HDR_DIR = ./libft
MLX_HDR_DIR = ./mlx
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))
#OBJ = $(SRC:.c=.o)
HDR = ./includes/rtv1.h ./includes/validation.h ./libft/libft.h ./mlx/mlx.h ./includes/test_render.h ./includes/fdf.h
LIB = libft/libft.a
MLX = mlx/lmlx.a
NAME = RTv1

all: $(NAME)

# %.o: src/%.c $(HDR)
# 	gcc -c $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HDR)
	gcc -g3  -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) -o $@ -c $<

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
	gcc -Wall -Wextra -Werror -g3 -o $(NAME) -I $(HDR_DIR) -I $(LIBFT_HDR_DIR) -I $(MLX_HDR_DIR) $(LIB) $(VAL) $(OBJ) -L mlx -lmlx -framework OpenGL -framework AppKit

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)
