/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/26 14:55:58 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		set_out(int *out, t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (!(tmp->type & IN))
		{
			if (tmp->type & TWO)
				*out = open(tmp->word, O_WRONLY | O_CREAT | O_APPEND, 0666);
			else
				*out = open(tmp->word,  O_WRONLY | O_CREAT | O_TRUNC, 0666);
			if (*out == -1)
				return (1);
			else
				return (0);
		}
		tmp = tmp->next;
	}
	*out = -1;
	return (0);
}

int		set_in(int	*in, t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	while (tmp)
	{
		if (tmp->type & IN)
		{
			if (!(tmp->type & TWO))
			{
				*in = open(tmp->word, O_RDONLY);
				if (*in == -1)
					return (1);
				else
					return (0);
			}
		}
		tmp = tmp->next;
	}
	*in = -1;
	return (0);
}

int	is_builtin(char *cmd) //change return
{
	if (ft_strcmp(cmd, "echoo"))
		return (0);
	else if (ft_strcmp(cmd, "cd"))
		return (0);
	else if (ft_strcmp(cmd, "pwd"))
		return (0);
	else if (ft_strcmp(cmd, "export"))
		return (0);
	else if (ft_strcmp(cmd, "unset"))
		return (0);
	else if (ft_strcmp(cmd, "env"))
		return (0);
	else if (ft_strcmp(cmd, "exit"))
		return (0);
	return (0);
}

int		cmd_nopipe(t_cmd *cmd)
{
	int	in;
	int	out;

	if (set_in(&in, cmd->redir))
		return (1);
	if (set_out(&out, cmd->redir))
		return (1);
	if (in != -1)
		if (dup2(in, STDIN_FILENO) == -1)
			return (1);
	if (out != -1)
		if (dup2(out, STDOUT_FILENO) == -1)
			return (1);
	if (is_builtin(cmd->cmd))
	{
		//printf("go built\n");
		//if (do_builtin(cmd))
			return (1);
	}
	else
	{
		if (execve("/usr/bin/echo", cmd->cm_argv, NULL))
		{
			perror("execve");
			return (1);
		}
	}
	return (0);
}

int		exec_cmd(t_cmd *cmd)
{
	pid_t	pid;

	if (!cmd)
		return (0);
	if (cmd->next)
	{
		//if (cmd_wpipe(cmd))
			return (1);
	}
	else
	{
		pid = fork();
		if (pid < 0)
			return (1);
		
		if (pid == 0)
			if (cmd_nopipe(cmd))
			{
				strerror(errno);
				return (1);
			}
	}
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