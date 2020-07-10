NAME = cub3d

SRC_DIR = srcs
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/get_next_line.c \
		$(SRC_DIR)/geometry_line.c \
		$(SRC_DIR)/geometry_rect.c \
		$(SRC_DIR)/input_check_args.c \
		$(SRC_DIR)/input_read_n_validate.c \
		$(SRC_DIR)/input_parse_identif.c \
		$(SRC_DIR)/input_parse_map.c \
		$(SRC_DIR)/vars_create_1.c \
		$(SRC_DIR)/vars_create_2.c \
		$(SRC_DIR)/game.c \
		$(SRC_DIR)/key_update.c \
		$(SRC_DIR)/raycast.c \
		$(SRC_DIR)/raycast_intercept.c \
		$(SRC_DIR)/render_2d.c \
		$(SRC_DIR)/render_3d.c \
		$(SRC_DIR)/sprite.c \
		$(SRC_DIR)/auxiliar_funct.c \
		$(SRC_DIR)/free_info.c \
		$(SRC_DIR)/error.c \
		$(SRC_DIR)/save_bmp_file.c \

INCLUDES = include

CC = clang

CFLAGS =	-Wall -Werror -Wextra -g -fsanitize=address

LFLAGS =	-lbsd -lm -lX11 -lXext \
			-L ./$(LIBFT_DIR) -lft \
			-L ./$(MLX_DIR) -lmlx

RM = /bin/rm -f

$(NAME):  $(SRC)
	make -C $(LIBFT_DIR)
	make -C $(MLX_DIR)
	$(CC) $(SRC) -I $(INCLUDES) $(CFLAGS) $(LFLAGS) -o $(NAME)

all: $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(OBJ)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PONY: all clean fclean re
