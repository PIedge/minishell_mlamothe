/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2021/12/15 12:32:37 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (0);
	else if (!ft_strcmp(cmd, "cd"))
		return (0);
	else if (!ft_strcmp(cmd, "pwd"))
		return (0);
	else if (!ft_strcmp(cmd, "export"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (0);
	else if (!ft_strcmp(cmd, "env"))
		return (0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	return (0);
}

int	do_cmd(t_cmd *cmd)
{
	if (is_builtin(cmd->cmd))
	{
		if (do_builtin(cmd))
			return (1);
		else
			return (0);
	}
	else
	{
		if (execve(cmd->cmd, cmd->cm_argv, NULL))
		{
			perror("execve");
			return (1);
		}
	}
	return (1);
}

int	cmd_wpipe(t_cmd *cmd)
{
	int		**pipefds;
	int		i;
	pid_t	pid;

	pipefds = get_pfd(cmd);
	if (!pipefds)
		return (1);
	if (pipe(pipefds[0]))
		return (1);
	if (first_child(pipefds[0][PIPE_R], pipefds[0][PIPE_W], cmd))
		return (1);
	i = 0;
	while (cmd->next->next && ++i)
	{
		if (pipe(pipefds[i]))
			return (1);
		if (other_childs(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], cmd))
			return (1);
	}
	if (last_child(cmd->next, pipefds[i][PIPE_R]))
		return (1);
	return (0);
}

int	cmd_nopipe(t_cmd *cmd)
{
	int		in;
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid)
		return (0);
	if (set_in_n_out(&in, &out, cmd->redir))
		return (1);
	if (do_cmd(cmd))
		return (1);
	return (0);
}

int	exec_cmd(t_cmd *cmd)
{
	pid_t	pid;
	t_cmd	*tmp;

	if (!cmd)
		return (0);
	tmp = cmd;
	if (check_paths_ok(tmp))
		return (1);
	if (tmp->next)
	{
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid)
			wait(0);
		else if (cmd_wpipe(tmp))
				return (1);
	}
	else
		if (cmd_nopipe(tmp))
			return (1);
	return (0);
}

int main (int argc, char **argv)
{
	t_cmd	cmd;
	t_redir	redir;

	redir.next = NULL;
	redir.prev = NULL;
	redir.word = argv[argc - 1];
	redir.type = 0;
	cmd.cmd = argv[1];
	cmd.next = NULL;
	cmd.prev = NULL;
	char **varg;
	if (!(varg = malloc(sizeof(char**))))
		return (1);
	varg[0] = argv[1];
	varg[1] = argv[2];
	varg[2] = NULL;
	cmd.cm_argv = varg;
	cmd.redir = &redir;
	exec_cmd(&cmd);
	return (0);
}