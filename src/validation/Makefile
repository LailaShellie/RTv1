
SRC = figure.c get_color.c get_parametr.c get_point_or_vector.c \
		get_type.c light.c parse_file.c parse_marks.c parsing_func.c \
		read_file.c validation_main.c

OBJ = $(SRC:.c=.o)

HDR = validation.h

NAME = validation.a

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

%.o: %.c $(HDR)
	gcc -Wall -Wextra -Werror -I $(HDR) -c $<
clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
