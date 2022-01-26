/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:11:26 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 20:57:33 by mlamothe         ###   ########.fr       */
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
		return (set_error(mini, 2, 1));
	if (first_child(pipefds[0][PIPE_R], pipefds[0][PIPE_W], cmd, mini))
		return (1);
	i = 0;
	while (cmd->next->next && ++i)
	{
		cmd = cmd->next;
		if (pipe(pipefds[i]))
			return (set_error(mini, 1, 2));
		if (other_childs(pipefds[i - 1][PIPE_R], pipefds[i][PIPE_W], \
			cmd, mini))
			return (1);
	}
	if (last_child(cmd->next, pipefds[i][PIPE_R], mini))
		return (1);
	while (--nb_cmds >= 0)
		waitpid(-1, NULL, WUNTRACED);
	exit(0);
}

int	cmd_nopipe(t_cmd *cmd, t_mini *mini)
{
	int		in;
	int		out;

	if (set_in_n_out(&in, &out, cmd, mini))
		exit (1);
	if (do_cmd(cmd, mini))
		exit (1);
	exit (0);
}

int	exec_cmd(t_cmd *cmd, int nb_cmds, t_mini *mini)
{
	pid_t	pid;
	t_cmd	*tmp;
	int		dup_in;
	int		dup_out;

	if (cmd->cm_argv[0] && !ft_strcmp(cmd->cm_argv[0], "exit"))
		return (0);
	if (exec_init(mini, cmd, &dup_in, &dup_out))
		return (ft_reset_dups(dup_in, dup_out, 2));
	tmp = cmd;
	pid = fork();
	if (pid < 0)
		return (set_error(mini, 4, 1));
	if (pid)
		waitpid(-1, NULL, WUNTRACED);
	else if (tmp->next)
	{
		if (cmd_wpipe(tmp, nb_cmds, mini))
			return (ft_reset_dups(dup_in, dup_out, 2));
	}
	else
		if (cmd_nopipe(tmp, mini))
			return (ft_reset_dups(dup_in, dup_out, 2));
	return (ft_reset_dups(dup_in, dup_out, 1));
}

char	*ft_here_doc(char *str, int i, t_mini *mini)
{
	int		fd;
	char	*rdline;
	char	*path;

	path = get_path_hd(mini, i);
	if (!path)
		return (NULL);
	fd = open(path, O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		free(path);
		return (NULL);
	}
	rdline = readline("> ");
	while (ft_strcmp(rdline, str))
	{
		write(fd, rdline, ft_strlen(rdline));
		write(fd, "\n", 1);
		rdline = readline("> ");
	}
	close (fd);
	return (path);
}
