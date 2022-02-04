/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:16:55 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 15:53:37 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ****************************************************************************
**							Includes									  	 **
******************************************************************************/

# include <sys/types.h>
# include <signal.h>
# include <sys/ucontext.h>
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

/* ****************************************************************************
**							Defines											 **
******************************************************************************/

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
# define N_VAR 24

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
# define E_VAR "Unknown variable : "

# define PIPE_R 0
# define PIPE_W 1

# ifndef __USE_POSIX
#  define __USE_POSIX
# endif
# ifndef __USE_MISC
#  define __USE_MISC
# endif

/* ****************************************************************************
**							Global											 **
******************************************************************************/

extern int					g_lrest;

/* ****************************************************************************
**							Structs											 **
******************************************************************************/

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
	char				*cmd_ori;
	t_cmd				*cmd;
	char				**env;
	int					err;
	char				*err_word;
	struct sigaction	old_c;
	struct sigaction	old_bs;
	struct sigaction	new_c;
	struct sigaction	new_exec_c;
	struct sigaction	new_bs;
	struct sigaction	lol;
}						t_mini;

/* ****************************************************************************
**							Functions									     **
******************************************************************************/

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
void	init_signals(t_mini *mini);
void	eof_in_cmd(t_mini *mini);
int		parse_some_things(t_mini *mini);
int		set_pipes(t_mini *mini);
int		cm_argv_creation(t_cmd *work);
int		var_treat_cmd(t_cmd *cmd, t_mini *mini);
void	strip_quote_cmd(t_cmd *cmd);

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
int		how_much_cmd(t_mini *mini);
int		in_if_find_redir(t_cmd *cmd, char *cm, int *i);
int		out_if_find_redir(t_cmd *cmd, char *cm, int *i);
t_redir	*new_redir(t_redir *prev, char *word, int type);
char	*get_redir_word(char *str, int *i);
void	norm_new_len(int *len, int *i);
void	norm_copy_var_into_new(char *ori, char *var, int *a, int i);
char	*norm_vts(char **new, int n_len);
void	copy_until_var(char *ori, char *new, int *i, int *y);
int		need_to_add(char *str, char **env, int *n_len);
int		get_end_index(char *str);
int		calc_new_len(char *str, char **env, int *n);

/*
** Utils for execution
*/
int		set_out(int *out, t_redir *redir, t_mini *mini);
int		set_in(int *in, t_redir *redir, t_mini *mini);
int		ft_closeem(int in, int out, int ret);
int		set_in_n_out(int *in, int *out, t_cmd *cmd, t_mini *mini);
int		**get_pfd(t_cmd *cmd, t_mini *mini);
int		ft_free_pipefds(int **pipefds, int ret, t_mini *mini);
int		check_paths_ok(t_cmd *cmd, t_mini *mini);
int		is_builtin(char *cmd);
int		ft_free_split(char	**splt, int ret);
char	*ft_join_cmd(char *str1, char *str2, t_mini *mini);
char	*ft_join(char *str1, char *str2, t_mini *mini);
void	ft_here_doc(char *str, t_mini *mini, int i);
int		handle_hd(t_mini *mini, t_redir *tmp);
char	*ft_strdup(const char *src, t_mini *mini);
int		ft_reset_dups(t_mini *mini, int in, int out);
char	*get_path_hd(t_mini *mini, int i);
void	ft_free_exit(t_mini *mini, int ret);
void	ft_free_exit_mltpipes(t_mini *mini, int **pipefds, int ret);
void	waitchild(int nb_cmds, t_mini *mini);
int		waitparent(int nb_cmds, t_mini *mini);

/*
** Execution' functions
*/

int		exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini);
int		exec_init(t_mini *mini, t_cmd *cmd, int *dup_in, int *dup_out);
int		first_child(int **pipefds, int i, t_cmd *cmd, t_mini *mini);
int		other_childs(int **pipefds, int i, t_cmd *cmd, t_mini *mini);
int		last_child(int **pipefds, int i, t_cmd *cmd, t_mini *mini);
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

void	ctrl_c(int sig);
void	ctrl_heredoc_c(int sig);

void	ctrl_cmd_c(int sig);
#endif
