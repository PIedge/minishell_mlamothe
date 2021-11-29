SRCS	=	\

NAME	=	minishell

CC		=	clang

FLAG	=	-Wall -Wextra -Werror

VALF	=	--tool=memcheck --leak-check=full --leak-resolution=high --show-reachable=yes --track-origins=yes --log-file=valgrind_log

OBJS	=	$(SRCS:.c=.o)

LNAME	=	libft.a

LPATH	=	./libft_re

.c.o:
		$(CC) $(FLAG) -c $< -o $(<:.c=.o)

all:	$(LNAME) $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(FLAG) $(OBJS) -o $(NAME)

${LNAME}:
			rm -f ${LNAME}
			make -C ${LPATH} all
			cp ${LPATH}/${LNAME} .

clean:
			make -C ${LPATH} fclean
			rm -f ${OBJS}

fclean: clean
			make -C ${LPATH} clean
			rm -f ${NAME}
			rm -f ${LNAME}

test:	$(LNAME)
			$(CC) $(FLAG) main_test.c

re:	fclean all

leaks:
		valgrind $(VALF) ./$(NAME)
		grep -A1 "valgrind" valgrind_log | grep ${NAME} || echo -n