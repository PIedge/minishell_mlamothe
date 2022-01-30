SRCS	=	srcs/inits_frees.c		\
			srcs/minishell.c		\
			srcs/split_pipes.c		\
			srcs/split_mini_utils.c	\
			srcs/ft_split_wp.c		\
			srcs/expansion.c		\
			srcs/var_utils.c		\
			srcs/mv_str.c			\
			srcs/redir_setup.c		\
			srcs/exec_childs.c		\
			srcs/exec_cmd.c			\
			srcs/exec_core.c		\
			srcs/exec_utils.c		\
			srcs/exec_path_finder.c	\
			srcs/get_pipefds.c		\
			srcs/set_in_out.c		\
			srcs/utils.c			\
			srcs/handle_errors.c	\
			builtins/ft_cd.c		\
			builtins/ft_echo.c		\
			builtins/ft_pwd.c		\
			builtins/ft_export.c	\
			builtins/ft_unset.c		\
			builtins/ft_env.c		\
			builtins/ft_exit.c		\
			main.c					\

NAME	=	minishell

CC		=	clang

FLAG	=	-Wall -Wextra -Werror -g3 -fsanitize=address

VALF	=	--tool=memcheck --leak-check=full --leak-resolution=high \
			--show-reachable=yes --track-origins=yes \
			--log-file=valgrind_log \
			--xtree-memory=full

OBJS	=	$(SRCS:.c=.o)

LNAME	=	libft.a

LPATH	=	./libft_re

.c.o:
		$(CC) $(FLAG) -c $< -o $(<:.c=.o)

all:	$(LNAME) $(NAME)

$(NAME):	$(OBJS)
				$(CC) $(FLAG) $(OBJS) $(LNAME) -I/usr/include/readline -lreadline -o $(NAME)

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

test:	$(LNAME) $(OBJS)
			$(CC) $(FLAG) main_test.c $(OBJS) $(LNAME)

re:	fclean all

leaks:
		valgrind $(VALF) ./$(NAME)
		grep -A1 "valgrind" valgrind_log | grep ${NAME} || echo -n