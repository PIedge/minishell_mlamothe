/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:16:55 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/25 17:27:18 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* *****************************************************************************
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
# include <readline/history.h>
# include <readline/readline.h>

/* *****************************************************************************
**							Defines											  **
*******************************************************************************/

# define INPUT "<\0"
# define OUTPUT ">\0"
# define HEREDOC "<<\0"
# define D_OUTPUT ">>\0"

# define PROMPT "\e[1;34mUwU\e[0m $ "
# define E_MALLOC "Malloc didn't work, your pc is probably dying\n"

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

char					**g_env;

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
** Every thing tagged with "//" at th eend means it might be temporary.
*/

typedef struct s_mini
{
	char	*cmd_ori;
	t_cmd	*cmd;
	char	**env;

}					t_mini;

/*
** Core functions
*/
void	destroy(t_mini *mini, char *str);
int		minishell(t_mini *mini);
char	*var_treat_str(char **str, char **env);
char	**copy_env(char **env);
char	*find_var(char **env, char *var_name);
char	*find_var_with_limit(char **env, char *start, char *end);
t_cmd	*find_redir(t_cmd *cmd, char *cm);

/*
** Split functions
*/
char	**ft_split_pipes(char *s, char c);
char	**ft_split_wp(char *s);

/*
** Utils style functions
*/
int		get_var_name_end(char *var);
void	skip_quotes(char *str, int *i, char c);
t_cmd	*create_cmd(t_cmd *prev);
t_redir	*create_redir(t_redir *prev, int type);
void	mv_str_left(char *str);

/*
** Utils for execution
*/
int		set_out(int *out, t_redir *redir);
int		set_in(int *in, t_redir *redir);
int		ft_closeem(int in, int out, int ret);
int		set_in_n_out(int *in, int *out, t_cmd *cmd);
int		**get_pfd(t_cmd *cmd);
int		ft_free_pipefds(int **pipefds, int ret);
int		check_paths_ok(t_cmd *cmd);
int		is_builtin(char *cmd);
char    *ft_join_cmd(char *str1, char *str2);

/*
** Execution' functions
*/

int		exec_cmd(t_cmd *cmd, int nb_cmds);
int		first_child(int pipe_r, int pipe_w, t_cmd *cmd);
int		other_childs(int pipe_r, int pipe_w, t_cmd *cmd);
int		last_child(t_cmd *cmd, int pipe_r);
int		do_cmd(t_cmd *cmd);
int		do_builtin(t_cmd *cmd);

/*
** Bultins fucntions
*/

int		ft_echo(t_cmd *cmd);
int		ft_cd(t_cmd *cmd);
int		ft_pwd(void);

int		ft_strcmp(char *s1, char *s2);

void	free_cmd(t_cmd *cmd);

#endif
