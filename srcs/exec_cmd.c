/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/28 10:17:11 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	cmd_wpipe(t_cmd *cmd, int nb_cmds, t_mini *mini)
{
	int		**pipefds;
	int		i;

	pipefds = get_pfd(cmd, mini);
	if (!pipefds)
		return (1);
	if (pipe(pipefds[0]))
		return (set_error(mini, N_PIPE, 1, NULL));
	if (first_child(pipefds[0][PIPE_R], pipefds[0][PIPE_W], cmd, mini))
		return (1);
	i = 0;
	while (cmd->next->next && ++i)
	{
		cmd = cmd->next;
		if (pipe(pipefds[i]))
			return (set_error(mini, N_FORK, 2, NULL));
		if (other_childs(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], \
			cmd, mini))
			return (1);
	}
	if (last_child(cmd->next, pipefds[i][PIPE_R], mini))
		return (1);
	while (--nb_cmds >= 0)
	{
		waitpid(-1, &mini->err, WUNTRACED);
		mini->err = WEXITSTATUS(mini->err);
	}
	return (ft_free_pipefds(pipefds, 0));
}

int	cmd_nopipe(t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

	if (set_in_n_out(&in, &out, cmd, mini))
		ft_free_exit(mini, mini->err);
	if (!cmd->cm_argv || !cmd->cm_argv[0])
		return (0);
	if (is_builtin(cmd->cm_argv[0]))
	{
		if (do_builtin(cmd, mini))
			return (1);
		else
			return (0);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			return (set_error(mini, N_FORK, 1, NULL));
		if (pid)
		{
			waitpid(-1, &mini->err, WUNTRACED);
			mini->err = WEXITSTATUS(mini->err);
		}
		else if (execve(cmd->cm_argv[0], cmd->cm_argv, mini->env))
		{
			set_error(mini, N_EXECVE, 1, NULL);
			ft_free_exit(mini, mini->err);
		}
	}
	return (0);
}

int	exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini)
{
	t_cmd	*tmp;
	int		dup_in;
	int		dup_out;

	if (cmd->cm_argv[0] && !ft_strcmp(cmd->cm_argv[0], "exit"))
		return (0);
	if (exec_init(mini, cmd, &dup_in, &dup_out))
		return (ft_reset_dups(dup_in, dup_out, 2));
	tmp = cmd;
	if (tmp->next)
	{
		if (cmd_wpipe(tmp, nb_cmds, mini))
			return (ft_reset_dups(dup_in, dup_out, 2));
	}
	else if (cmd_nopipe(tmp, mini))
		return (ft_reset_dups(dup_in, dup_out, 2));
	return (ft_reset_dups(dup_in, dup_out, 1));
}

char	*ft_here_doc(char *str, int i, t_mini *mini)
{
	int		fd;
	char	*rdline;
	char	*path;

	path = get_path_hd(mini, i);
	if (!path)
		return (NULL);
	fd = open(path, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		free(path);
		return (NULL);
	}
	rdline = readline("> ");
	while (ft_strcmp(rdline, str))
	{
		write(fd, rdline, ft_strlen(rdline));
		write(fd, "\n", 1);
		rdline = readline("> ");
	}
	close (fd);
	return (path);
}
