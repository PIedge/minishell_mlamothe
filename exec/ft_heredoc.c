/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:13:52 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/03 11:39:06 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	handle_hd(t_mini *mini, t_redir *tmp)
{
	pid_t		pid;
	static int	i = 1;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid)
	{
		free(tmp->word);
		tmp->word = get_path_hd(mini, i);
		if (waitparent(1, mini))
			return (1);
	}
	else
		ft_here_doc(tmp->word, mini, i);
	++i;
	return (0);
}

void	ft_warn_heredoc(int fd, char *str, t_mini *mini, int ret)
{
	if (ret)
	{
		printf("minishell: warning: here-document" \
			" delimited by EOF (wanted \'%s\')\n", str);
	}
	close(fd);
	ft_free_exit(mini, mini->err);
}

void	loop_read_hd(char *str, t_mini *mini, int fd)
{
	char	*rdline;

	rdline = readline("> ");
	if (!rdline)
		ft_warn_heredoc(fd, str, mini, 1);
	while (ft_strcmp(rdline, str))
	{
		write(fd, rdline, ft_strlen(rdline));
		write(fd, "\n", 1);
		rdline = readline("> ");
		if (!rdline)
			ft_warn_heredoc(fd, str, mini, 1);
	}
}

void	ft_here_doc(char *str, t_mini *mini, int i)
{
	int		fd;
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
	loop_read_hd(str, mini, fd);
	ft_warn_heredoc(fd, str, mini, 0);
}
