NAME = a.out

SRC_DIR = srcs
GNL_DIR = gnl
LIBFT_DIR = libft

SRC =	$(SRC_DIR)/main.c \
		$(SRC_DIR)/create_vars.c \
		$(SRC_DIR)/init_game.c \
		$(SRC_DIR)/raycast.c \
		$(SRC_DIR)/calculate_interception.c \
		$(SRC_DIR)/map2d_player.c \
		$(SRC_DIR)/player_move.c \
		$(SRC_DIR)/projection3d.c \
		$(SRC_DIR)/map.c \
		$(SRC_DIR)/text_colors.c \
		$(SRC_DIR)/sprite.c \
		$(SRC_DIR)/geometry.c \
		$(SRC_DIR)/aux.c \
		$(SRC_DIR)/validate_file.c \
		$(SRC_DIR)/parse_identif.c \
		$(SRC_DIR)/parse_map.c \
		$(GNL_DIR)/get_next_line.c \

OBJ = $(SRC:.c=.o)

INCLUDES = include

CC = clang

CFLAGS =	-Wall -Werror -Wextra -g -fsanitize=address

LFLAGS =	-lbsd -lmlx -lm -lX11 -lXext \
			-L ./$(LIBFT_DIR) -lft

RM = /bin/rm -f

$(NAME):
	@ make -C $(LIBFT_DIR)
	@ $(CC) $(SRC) -I $(INCLUDES) $(CFLAGS) $(LFLAGS) -o a.out

all: $(NAME)

clean:
	@ make clean -C $(LIBFT_DIR)
	@ $(RM) $(OBJ)

fclean: clean
	@ make fclean -C $(LIBFT_DIR)
	@ $(RM) $(NAME)

re: fclean all

.PONY: all clean fclean re
