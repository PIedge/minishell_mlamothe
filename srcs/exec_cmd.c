/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/24 19:01:50 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
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

int	do_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->cm_argv[0], "echo"))
		return (ft_echo(cmd));
	else if (!ft_strcmp(cmd->cm_argv[0], "cd"))
		return (ft_cd(cmd));
	else if (!ft_strcmp(cmd->cm_argv[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(cmd->cm_argv[0], "export"))
		return (0);
	else if (!ft_strcmp(cmd->cm_argv[0], "unset"))
		return (0);
	else if (!ft_strcmp(cmd->cm_argv[0], "env"))
		return (0);
	else if (!ft_strcmp(cmd->cm_argv[0], "exit"))
		return (0);
	return (0);
}

int	do_cmd(t_cmd *cmd)
{
	if (is_builtin(cmd->cm_argv[0]))
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
		if (other_childs(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], \
			 cmd))
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
	if (set_in_n_out(&in, &out, cmd))
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
		return (1);
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
	{
		if (cmd_nopipe(tmp))
			return (1);
	}
	return (0);
}

int	ft_here_doc(char *str)
{
	int		fd;
	char	*rdline;

																//Check si écriture ok dans /tmp
	fd = open("/tmp/minishell-here_doc", O_WRONLY, O_CREAT);
	if (fd == -1)
		return (1);
	rdline = ft_readline(NULL);
	while(ft_strcmp(rdline, str))
	{
		write(fd, rdline, ft_strlen(rdline));
		rdline = ft_readline(NULL);
	}
	close (fd);
	fd = open("/tmp/minishell-here_doc", O_RDONLY);
	if (fd == -1)
		return (1);
	if (unlink("/tmp/minishell-here_doc"))
		return (1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (1);
																// CHECK SI NE PAS LE CLOSE CA PUE
	return (0);
}