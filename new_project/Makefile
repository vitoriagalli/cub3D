all:
	@ clang srcs/*.c \
	-I include \
	-Wall -Werror -Wextra \
	-lmlx -lm -lX11 -lXext \
	-lbsd -g -fsanitize=address \
	-o a.out

fclean:
	@ /bin/rm -f a.out

re: fclean all

.PONY: all clean fclean re
