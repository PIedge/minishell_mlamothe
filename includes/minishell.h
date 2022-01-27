/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:16:55 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/27 16:12:13 by mlamothe         ###   ########.fr       */
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

# define N_MALLOC 2
# define N_PIPE 3
# define N_DUP2 4
# define N_FORK 5
# define N_OPENDIR 6
# define N_OPEN 7
# define N_UNLINK 8
# define N_ACCESS 9
# define N_EXECVE 10
# define N_CDMARGS 20
# define N_CDFARGS 21
# define N_CDCHDIR 22
# define N_PWD 23

# define E_MALLOC "Malloc didn't work, your pc is probably dying\n"
# define E_PIPE "Error with pipe\n"
# define E_DUP2 "Error with dup2\n"
# define E_FORK "Error with fork\n"
# define E_OPENDIR "Error with opendir\n"
# define E_OPEN "Error with open\n"
# define E_UNLINK "Error with unlink\n"
# define E_ACCESS "Error with access\n"
# define E_EXECVE "Error with execve\n"
# define E_CDMARGS "cd : too many args\n"
# define E_CDFARGS "cd : too few args\n"
# define E_CDCHDIR "Error with chdir in cd\n"
# define E_PWD "Error, can\'t get pwd because of getcwd\n"

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
** Every thing tagged with "//" at th eend means it might be temporary.
*/

typedef struct s_mini
{
	char	*cmd_ori;
	t_cmd	*cmd;
	char	**env;
	int		err;
	char	*err_word;
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
t_cmd	*find_redir(t_cmd *cmd, char *cm, t_mini *mini);

/*
** Split functions
*/
char	**ft_split_pipes(char *s, char c);
char	**ft_split_wp(char *s);

/*
** Utils style functions
*/
int		get_var_name_end(char *var, t_mini *mini);
void	skip_quotes(char *str, int *i, char c);
t_cmd	*create_cmd(t_cmd *prev);
t_redir	*create_redir(t_redir *prev, int type);
void	mv_str_left(char *str);
int		ft_atoi(const char *str);
int		ft_strcmp(char *s1, char *s2);
void	free_cmd(t_cmd *cmd);
int		set_error(t_mini *mini, int err, int ret, char *str);
void	select_err(int err, char *str);

/*
** Utils for execution
*/
int		set_out(int *out, t_redir *redir, t_mini *mini);
int		set_in(int *in, t_redir *redir, t_mini *mini);
int		ft_closeem(int in, int out, int ret);
int		set_in_n_out(int *in, int *out, t_cmd *cmd, t_mini *mini);
int		**get_pfd(t_cmd *cmd, t_mini *mini);
int		ft_free_pipefds(int **pipefds, int ret);
int		check_paths_ok(t_cmd *cmd, t_mini *mini);
int		is_builtin(char *cmd);
char    *ft_join_cmd(char *str1, char *str2, t_mini *mini);
char	*ft_join(char *str1, char *str2, t_mini *mini);
char	*ft_here_doc(char *str, int i, t_mini *mini);
char    *ft_strdup(const char *src, t_mini *mini);
int		ft_reset_dups(int in, int out, int ret);
char	*get_path_hd(t_mini *mini, int i);
void	ft_free_exit(t_mini *mini, int ret);

/*
** Execution' functions
*/

int		exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini);
int		exec_init(t_mini *mini, t_cmd *cmd, int *dup_in, int *dup_out);
int		first_child(int pipe_r, int pipe_w, t_cmd *cmd, t_mini *mini);
int		other_childs(int pipe_r, int pipe_w, t_cmd *cmd, t_mini *mini);
int		last_child(t_cmd *cmd, int pipe_r, t_mini *mini);
int		do_cmd(t_cmd *cmd, t_mini *mini);
int		do_builtin(t_cmd *cmd, t_mini *mini);
int		is_builtin(char	*cmd);
int		do_cmd(t_cmd *cmd, t_mini *mini);

/*
** Bultins fucntions
*/

int		ft_echo(t_cmd *cmd, t_mini *mini);
int		ft_cd(t_cmd *cmd, t_mini *mini);
int		ft_pwd(t_mini *mini);
int		ft_export(t_cmd *cmd, t_mini *mini);
int		ft_unset(t_cmd *cmd, t_mini *mini);
int		ft_env(t_cmd *cmd, t_mini *mini);
int		ft_exit(t_mini *mini);

#endif
