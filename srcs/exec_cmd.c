/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/01 18:59:35 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

void	waitall(int nb_cmds, t_mini *mini)
{
	int	status;

	while (--nb_cmds >= 0)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			WTERMSIG(status);
			g_lrest = 130;
			mini->err = status;
		}
		else
		{
			if (WEXITSTATUS(status))
				g_lrest = 1;
			else
				g_lrest = 0;
			mini->err = status;
		}
	}
}

void	waithd(t_mini *mini)
{
	int	status;

	waitpid(-1, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		WTERMSIG(status);
		g_lrest = 130;
		mini->err = status;
	}
	else
	{
		WEXITSTATUS(status);
		mini->err = status;
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
	waitall(nb_cmds, mini);
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
		if (pid < 0)
			return (set_error(mini, N_FORK, 1, NULL));
		if (pid)
			waitall(1, mini);
		else if (execve(cmd->cm_argv[0], cmd->cm_argv, mini->env))
		{
			set_error(mini, N_EXECVE, 1, NULL);
			ft_free_exit(mini, g_lrest);
		}
	}
	return (0);
}

int	exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini)
{
	t_cmd	*tmp;
	int		dup_in;
	int		dup_out;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (set_error(mini, N_FORK, 2, NULL));
	if (pid)
		waithd(mini);
	else
	{
		if (cmd->cm_argv[0] && !ft_strcmp(cmd->cm_argv[0], "exit"))
			exit(0);
		if (exec_init(mini, cmd, &dup_in, &dup_out))
			ft_reset_dups(mini, dup_in, dup_out);
		tmp = cmd;
		if (tmp->next)
			cmd_wpipe(tmp, nb_cmds, mini);
		else
			cmd_nopipe(tmp, mini);
		ft_reset_dups(mini, dup_in, dup_out);
	}
	return (1);
}

char	*ft_warn_heredoc(int fd, char *str, int ret)
{
	if (ret)
	{
		printf("minishell: warning: here-document" \
			" delimited by EOF (wanted \'%s\')\n", str);
	}
	close(fd);
	return (NULL);
}

char	*ft_here_doc(char *str, t_mini *mini, int i)
{
	int		fd;
	char	*rdline;
	char	*p_hd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	p_hd = get_path_hd(mini, i);
		if (!p_hd)
			return (NULL);
	fd = open(p_hd, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		free(p_hd);
		ft_free_exit(mini, mini->err);
	}
	rdline = readline("> ");
	if (!rdline)
		ft_warn_heredoc(fd, str, 1);
	while (ft_strcmp(rdline, str))
	{
		write(fd, rdline, ft_strlen(rdline));
		write(fd, "\n", 1);
		rdline = readline("> ");
		if (!rdline)
			return (ft_warn_heredoc(fd, str, 1));
	}
	ft_warn_heredoc(fd, str, 0);
	return (p_hd);
}
