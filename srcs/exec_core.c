/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:13:06 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/01 13:20:21 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_reset_dups(t_mini *mini, int in, int out, int ret)
{
	signal(SIGINT, mini->new_c.sa_handler);
	signal(SIGQUIT, SIG_IGN);
	if (dup2(in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(out, STDOUT_FILENO) == -1)
		return (1);
	return (ret);
}

int	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	do_builtin(t_cmd *cmd, t_mini *mini)
{
	if (!ft_strcmp(cmd->cm_argv[0], "echo"))
		return (ft_echo(cmd, mini));
	else if (!ft_strcmp(cmd->cm_argv[0], "cd"))
		return (ft_cd(cmd, mini));
	else if (!ft_strcmp(cmd->cm_argv[0], "pwd"))
		return (ft_pwd(mini));
	else if (!ft_strcmp(cmd->cm_argv[0], "export"))
		return (ft_export(cmd, mini));
	else if (!ft_strcmp(cmd->cm_argv[0], "unset"))
		return (ft_unset(cmd, mini));
	else if (!ft_strcmp(cmd->cm_argv[0], "env"))
		return (ft_env(cmd, mini));
	else if (!ft_strcmp(cmd->cm_argv[0], "exit"))
		return (ft_exit(mini));
	return (0);
}

int	do_cmd(t_cmd *cmd, t_mini *mini)
{
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
		if (execve(cmd->cm_argv[0], cmd->cm_argv, mini->env))
			return (set_error(mini, N_EXECVE, 1, NULL));
	}
	return (1);
}
