/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/02/04 11:10:47 by mlamothe         ###   ########.fr       */
=======
/*   Updated: 2022/02/04 08:41:32 by tmerrien         ###   ########.fr       */
>>>>>>> 69b6cba3730265111dc217c05e6a0f488702d1bb
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
	cmd = cmd->next;
	i = 0;
	while (cmd->next && ++i)
	{
		if (pipe(pipefds[i]))
			return (set_error(mini, N_FORK, 2, NULL));
		if (other_childs(pipefds, i, cmd, mini))
			return (1);
		cmd = cmd->next;
	}
	if (last_child(cmd, pipefds[i][PIPE_R], mini))
		return (1);
	waitparent(nb_cmds, mini);
	return (0);
}

int	fork_nopipe(t_cmd *cmd, t_mini *mini)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (set_error(mini, N_FORK, 1, NULL));
	if (pid)
		waitparent(1, mini);
	else
	{
		sigaction(SIGINT, &mini->old_c, NULL);
		if (execve(cmd->cm_argv[0], cmd->cm_argv, mini->env))
		{
			set_error(mini, N_EXECVE, 1, NULL);
			ft_free_exit(mini, g_lrest);
		}
	}
	return (0);
}

int	cmd_nopipe(t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;

	if (set_in_n_out(&in, &out, cmd, mini))
		return (1);
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
		return (fork_nopipe(cmd, mini));
	return (0);
}

int	exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini)
{
	t_cmd	*tmp;
	int		dup_in;
	int		dup_out;

	signal(SIGINT, SIG_IGN);
	if (cmd->cm_argv[0] && !cmd->next && \
		!ft_strcmp(cmd->cm_argv[0], "exit"))
	{
		mini->err = 0;
		return (0);
	}
	if (exec_init(mini, cmd, &dup_in, &dup_out))
		return (2);
	tmp = cmd;
	if (tmp->next)
		cmd_wpipe(tmp, nb_cmds, mini);
	else
		cmd_nopipe(tmp, mini);
	return (ft_reset_dups(mini, dup_in, dup_out));
}
