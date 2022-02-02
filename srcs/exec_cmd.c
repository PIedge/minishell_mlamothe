/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/02 01:10:17 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

void ft_free_kill(t_mini *mini)
{
	free(mini->cmd_ori);
	free_cmd(mini->cmd);
	ft_double_tab_free(mini->env);
	rl_clear_history();
	kill(0, SIGTERM);
}

void	waitchild(int nb_cmds, t_mini *mini)
{
	int	status;

	while (--nb_cmds >= 0)
	{
		waitpid(-1, &status, WUNTRACED);
		//printf("status : %d\n", status >> 8);
		//printf("g_lrest : %d\n", g_lrest);
		if (WIFSIGNALED(status))
		{
			//printf("signaled\n");
			if (WTERMSIG(status) || g_lrest == 130)
			{
				ft_free_exit(mini, mini->err);
			}
			mini->err = status;
			g_lrest = 130;
		}
		else
		{
			g_lrest = status >> 8;
			mini->err = status;
		}
	}
}

void	waitparent(t_mini *mini)
{
	int	status;

	waitpid(-1, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		g_lrest = status >> 8;
		if (WTERMSIG(status))
			g_lrest = 130;
		mini->err = status >> 8;
	}
	else
	{
		WEXITSTATUS(status);
		mini->err = status >> 8;
		if (status)
			g_lrest = 1;
	}
}

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
	waitchild(nb_cmds, mini);
	return (ft_free_pipefds(pipefds, 0, mini));
}

int	cmd_nopipe(t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;
	pid_t	pid;

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
	{
		pid = fork();
		if (pid == -1)
			return (set_error(mini, N_FORK, 1, NULL));
		if (pid)
			waitchild(1, mini);
		else if (execve(cmd->cm_argv[0], cmd->cm_argv, mini->env))
		{
			set_error(mini, N_EXECVE, 1, NULL);
			ft_free_exit(mini, g_lrest);
		}
	}
	return (0);
}

int	select_return(t_mini *mini)
{
	if (mini->err == 1 || mini->err == 0)
		return (1);
	return (2);
}

int	exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini)
{
	t_cmd	*tmp;
	int		dup_in;
	int		dup_out;
	pid_t	pid;

	//sigaction(SIGINT, &mini->old_c, &mini->old_c);
	if (cmd->cm_argv[0] && !ft_strcmp(cmd->cm_argv[0], "exit"))
	{
		mini->err = 0;
		return (0);
	}
	if (exec_init(mini, cmd, &dup_in, &dup_out))
			return (2);
	pid = fork();
	if (pid == -1)
		return (set_error(mini, N_FORK, 2, NULL));
	if (pid)
		waitparent(mini);
	else
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		tmp = cmd;
		if (tmp->next)
			cmd_wpipe(tmp, nb_cmds, mini);
		else
			cmd_nopipe(tmp, mini);
		ft_reset_dups(mini, dup_in, dup_out);
	}
	return (select_return(mini));
}

void	ft_warn_heredoc(int fd, char *str, t_mini *mini)
{
	if (mini->err)
	{
		printf("minishell: warning: here-document" \
			" delimited by EOF (wanted \'%s\')\n", str);
	}
	close(fd);
	ft_free_exit(mini, mini->err);
}

void	ft_here_doc(char *str, t_mini *mini, int i)
{
	int		fd;
	char	*rdline;
	char	*p_hd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	p_hd = get_path_hd(mini, i);
		if (!p_hd)
			ft_free_exit(mini, mini->err);
	fd = open(p_hd, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		free(p_hd);
		ft_free_exit(mini, mini->err);
	}
	rdline = readline("> ");
	if (!rdline)
		ft_warn_heredoc(fd, str, mini);
	while (ft_strcmp(rdline, str))
	{
		write(fd, rdline, ft_strlen(rdline));
		write(fd, "\n", 1);
		rdline = readline("> ");
		if (!rdline)
			ft_warn_heredoc(fd, str, mini);
	}
	ft_warn_heredoc(fd, str, mini);
}
