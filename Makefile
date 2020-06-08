NAME = a.out

SRC_DIR = srcs
GNL_DIR = gnl
# INPUT_DIR = input
# ENGINE_DIR = engine
# AUX_DIR = aux
# UTIL_DIR = utils

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
		$(SRC_DIR)/geometry.c \
		$(SRC_DIR)/aux.c \
		$(SRC_DIR)/validate_file.c \
		$(SRC_DIR)/parse_identif.c \
		$(SRC_DIR)/parse_map.c \
		$(SRC_DIR)/utils_str.c \
		$(SRC_DIR)/utils_char.c \
		$(SRC_DIR)/utils_memory.c \
		$(GNL_DIR)/get_next_line.c \

OBJ = *.o

INCLUDES = include

CC = clang

CFLAGS =	-Wall -Werror -Wextra -g -fsanitize=address

LFLAGS =	-lbsd -lmlx -lm -lX11 -lXext

RM = /bin/rm -f

$(NAME):
	@ $(CC) $(SRC) -I $(INCLUDES) $(CFLAGS) $(LFLAGS) -o a.out

all: $(NAME)

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PONY: all clean fclean re
