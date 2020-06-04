# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vscabell <vscabell@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/06/04 16:22:59 by vscabell          #+#    #+#              #
#    Updated: 2020/06/04 17:36:19 by vscabell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

SRC =	get_next_line.c \
		get_next_line_utils.c

OBJ =	get_next_line.o \
		get_next_line_utils.o

CC = clang

CFLAGS = -Wall -Werror -Wextra

RM = /bin/rm -f

all: $(NAME)

$(NAME):
	@ $(CC) $(CFLAGS) -c $(SRC)
	@ ar rc $(NAME) $(OBJ)
	@ ranlib $(NAME)

clean:
	@ $(RM) $(OBJ)

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
