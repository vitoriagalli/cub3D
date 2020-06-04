NAME = cub3d.out

SRC_DIR = srcs

SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/create_vars.c \
		$(SRC_DIR)/init_game.c \
		$(SRC_DIR)/raycast.c \
		$(SRC_DIR)/calculate_interception.c \
		$(SRC_DIR)/map2d_player.c \
		$(SRC_DIR)/player_move.c \
		$(SRC_DIR)/projection3d.c \
		$(SRC_DIR)/textures.c \
		$(SRC_DIR)/color.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/geometry.c \
		$(SRC_DIR)/map.c \
		$(SRC_DIR)/get_next_line_utils.c \
		$(SRC_DIR)/get_next_line.c \

OBJ = *.o

INCLUDES = include

CC = clang

CFLAGS = -Wall -Werror -Wextra -g -fsanitize=address

LFLAGS = -lbsd -lmlx -lm -lX11 -lXext

RM = /bin/rm -f

$(NAME):
	@ $(CC) $(SRC) -I $(INCLUDES) $(CFLAGS) $(LFLAGS) -o $(NAME)

clean:
	@ $(RM) $(OBJ)

fclean:
	@ $(RM) $(NAME)

re: fclean all

.PONY: all clean fclean re
