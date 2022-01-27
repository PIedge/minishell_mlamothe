/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:16:19 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/27 01:26:05 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	first_child(int pipe_r, int pipe_w, t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_free_exit(mini, 1);
	if (pid == 0)
	{
		close(pipe_r);
		if (set_in_n_out(&in, &out, cmd, mini))
			ft_free_exit(mini, 1);
		if (out == -1)
			if (dup2(pipe_w, STDOUT_FILENO) == -1)
				ft_free_exit(mini, 1);
		close(pipe_w);
		if (do_cmd(cmd, mini))
			ft_free_exit(mini, 1);
		ft_free_exit(mini, 0);
	}
	cmd = cmd->next;
	close(pipe_w);
	return (0);
}

int	other_childs(int pipe_r, int pipe_w, t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_free_exit(mini, 1);
	if (pid == 0)
	{
		if (set_in_n_out(&in, &out, cmd, mini))
			ft_free_exit(mini, 1);
		if (in == -1)
			if (dup2(pipe_r, STDIN_FILENO) == -1)
				ft_free_exit(mini, 1);
		if (out == -1)
			if (dup2(pipe_w, STDOUT_FILENO) == -1)
				ft_free_exit(mini, 1);
		ft_closeem(pipe_r, pipe_w, 0);
		if (do_cmd(cmd, mini))
			ft_free_exit(mini, 1);
		ft_free_exit(mini, 0);
	}
	return (ft_closeem(pipe_r, pipe_w, 0));
}

int	last_child(t_cmd *cmd, int pipe_r, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_free_exit(mini, 1);
	if (pid == 0)
	{
		if (set_in_n_out(&in, &out, cmd, mini))
			ft_free_exit(mini, 1);
		if (in == -1)
			if (dup2(pipe_r, STDIN_FILENO) == -1)
				ft_free_exit(mini, 1);
		close(pipe_r);
		if (do_cmd(cmd, mini))
			ft_free_exit(mini, 1);
		ft_free_exit(mini, 0);
	}
	close(pipe_r);
	return (0);
}
