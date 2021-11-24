/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2021/11/24 15:14:33 by mlamothe         ###   ########.fr       */
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

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo"))
		echo;
	else if (ft_strcmp(cmd, "cd"))
		echo;
	else if (ft_strcmp(cmd, "pwd"))
		echo;
	else if (ft_strcmp(cmd, "export"))
		echo;
	else if (ft_strcmp(cmd, "unset"))
		echo;
	else if (ft_strcmp(cmd, "env"))
		echo;
	else if (ft_strcmp(cmd, "exit"))
		echo;
	return (0);
}

int		cmd_nopipe(t_cmd *cmd, t_redir *redir)
{
	int	in;
	int	out;

	if (set_in(&in, redir))
		return (1);
	if (set_out(&in, redir))
		return (1);
	if (in != -1)
		if (dup2(STDIN_FILENO, in) == -1)
			return (1);
	if (out != -1)
		if (dup2(STDOUT_FILENO, out) == -1)
			return (1);
	if (is_builtin(cmd->cmd))
	{
		if (do_builtin(cmd, redir))
			return (1);
	}
	else
		if (execve())
			return (1);
	return (0);
}

int		exec_cmd(t_cmd *cmd, t_redir *redir)
{
	pid_t	pid;

	if (!cmd)
		return (0);
	if (cmd->next)
	{
		if (cmd_wpipe(cmd, redir))
			return (1);
	}
	else
	{
		pid = fork();
		if (!pid)
			return (1);
		if (pid == 0)
			if (cmd_nopipe(cmd, redir));
				return (1);
	}
	return (0);
}