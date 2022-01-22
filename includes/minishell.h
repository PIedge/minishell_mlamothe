/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:16:55 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/22 13:10:25 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*******************************************************************************
**							Includes										  **
*******************************************************************************/

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <dirent.h>
# include <readline/readline.h> //may have to delete it later
# include <readline/history.h>  //may have to delete it later

/* *****************************************************************************
**							Defines											  **
*******************************************************************************/

# define PIPE_R 0
# define PIPE_W 1

/* *****************************************************************************
**							Structs											  **
*******************************************************************************/

/*
** The s_redir is a double chained list containing "word" a char* wich is
** the name of the file to redirect to.
** The type variable has been explained above in the Defines section.
*/

typedef struct s_redir
{
	struct s_redir	*next;
	struct s_redir	*prev;
	char			*word;
	int				type;
}					t_redir;

/*
** The s_cmd is a double chained list and behave as a pipe, meaning each element
** of this list is a pipe (ofc if there's only one element then it's not a pipe).
** cmd contains the entire command for the pipe.
** cmd_argv contains arguments for the command behaves like argv in C.
** Well redir is redir.
*/

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*cmd;
	char			**cm_argv;
	t_redir			*in;
	t_redir			*out;
}					t_cmd;

/*
** Main struture for minishell contains every thing that should be freed in case
** of an error.
*/

typedef struct s_map
{
	char	**key;
	char	**value;
}					t_map;

typedef struct s_mini
{
	char	*cmd_ori;
	t_cmd	*cmd;
	t_map	env;
}					t_mini;

int			exec_cmd(t_cmd *cmd, t_map env);

int			ft_strlen(char *str);

int			ft_strcmp(char *s1, char *s2);

int			set_out(int *out, t_redir *redir);

int			set_in(int *in, t_redir *redir);

int			ft_closeem(int in, int out, int ret);

int			set_in_n_out(int *in, int *out, t_cmd *cmd);

int			**get_pfd(t_cmd *cmd);

int			ft_free_pipefds(int **pipefds, int ret);

int			first_child(int pipe_r, int pipe_w, t_cmd *cmd, t_map env);

int			other_childs(int pipe_r, int pipe_w, t_cmd *cmd, t_map env);

int			last_child(t_cmd *cmd, int pipe_r, t_map env);

int			check_paths_ok(t_cmd *cmd, t_map env);

int			ft_echo(t_cmd *cmd, t_map env);

int			do_cmd(t_cmd *cmd, t_map env);

int			is_builtin(char *cmd, t_map env);

char		*ft_get_var(char *var_name, t_map env);

int			do_builtin(char *cmd, t_map env);

#endif