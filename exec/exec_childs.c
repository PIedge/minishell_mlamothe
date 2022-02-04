/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_childs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:16:19 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 11:18:00 by mlamothe         ###   ########.fr       */
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
	if (pid == -1 && ft_closeem(pipe_r, pipe_w, 1))
		return (set_error(mini, N_FORK, 1, NULL));
	if (!pid)
	{
		sigaction(SIGINT, &mini->old_c, NULL);
		close(pipe_r);
		if (set_in_n_out(&in, &out, cmd, mini))
			ft_free_exit(mini, mini->err);
		if (out == -1)
			if (dup2(pipe_w, STDOUT_FILENO) == -1)
				ft_free_exit(mini, mini->err);
		close(pipe_w);
		if (do_cmd(cmd, mini))
			ft_free_exit(mini, mini->err);
		ft_free_exit(mini, mini->err);
	}
	close(pipe_w);
	return (0);
}

int	other_childs(int **pipefds, int i, t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid == -1 && ft_closeem(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], 1) \
		&& !close(pipefds[i][PIPE_R]))
		return (set_error(mini, N_FORK, 1, NULL));
	if (!pid)
	{
		sigaction(SIGINT, &mini->old_c, NULL);
		if (set_in_n_out(&in, &out, cmd, mini))
			ft_free_exit(mini, mini->err);
		if (in == -1)
			if (dup2(pipefds[i - 1][PIPE_R], STDIN_FILENO) == -1)
				ft_free_exit(mini, mini->err);
		if (out == -1)
			if (dup2(pipefds[i][PIPE_W], STDOUT_FILENO) == -1)
				ft_free_exit(mini, mini->err);
		ft_closeem(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], 0);
		close(pipefds[i][PIPE_R]);
		do_cmd(cmd, mini);
		ft_free_exit(mini, mini->err);
	}
	return (ft_closeem(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], 0));
}

int	last_child(t_cmd *cmd, int pipe_r, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

	pid = fork();
	if (pid == -1 && !close(pipe_r))
		return (set_error(mini, N_FORK, 1, NULL));
	if (!pid)
	{
		sigaction(SIGINT, &mini->old_c, NULL);
		if (set_in_n_out(&in, &out, cmd, mini))
			ft_free_exit(mini, mini->err);
		if (in == -1)
			if (dup2(pipe_r, STDIN_FILENO) == -1)
				ft_free_exit(mini, mini->err);
		close(pipe_r);
		if (do_cmd(cmd, mini))
			ft_free_exit(mini, mini->err);
		ft_free_exit(mini, mini->err);
	}
	close(pipe_r);
	return (0);
}
