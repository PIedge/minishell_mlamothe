SRCS	=	ft_printf_double_tab.c	\
			ft_double_tab_free.c	\
			ft_readline.c			\
			ft_strcpy.c				\
			ft_strlen.c				\
			ft_memcpy.c				\
			ft_is_white_space.c		\
			ft_substr.c				\
			ft_strncmp.c			\
			ft_realloc.c			\

NAME	=	libft.a

CC		=	clang

FLAG	=	-Wall -Wextra -Werror

VALF	=	--tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes --log-file=valgrind_log

OBJS	=	$(SRCS:.c=.o)

.c.o:
		$(CC) $(FLAG) -c $< -o $(<:.c=.o)

.PHONY: all
all:	$(NAME)

$(NAME):	$(OBJS)
				ar rc $(NAME) $(OBJS)
				ranlib $(NAME)

.PHONY: clean
clean:
				rm -f $(OBJS)

.PHONY: fclean
fclean:		clean
				rm -f $(NAME)

.PHONY: re
re:			fclean all