/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 12:20:08 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <sys/types.h>
#include <signal.h>
#include <sys/ucontext.h>
#include <unistd.h>

void	ctrl_c(int sig)
{
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	sig = 0;
	g_lrest = 130;
}

void	ctrl_cmd_c(int sig)
{
	sig = 0;
	g_lrest = 130;
	exit(3);
}

void	ctrl_heredoc_c(int sig)
{
	printf("\n");
	exit(3);
	sig = 0;
	g_lrest = 130;
}

void	ctrl_back(int sig)
{
	rl_replace_line("", 1);
	rl_redisplay();
	sig = 0;
	g_lrest = 0;
}

void	init_signals(t_mini *mini)
{
	signal(SIGQUIT, SIG_IGN);
	ft_bzero((void *)&mini->new_c, sizeof(mini->new_c));
	ft_bzero((void *)&mini->new_exec_c, sizeof(mini->new_exec_c));
	ft_bzero((void *)&mini->lol, sizeof(mini->lol));
	mini->new_c.sa_handler = ctrl_c;
	mini->new_c.sa_flags = 0;
	ft_bzero((void *)&mini->new_c.sa_mask, sizeof(__sigset_t *));
	mini->lol.sa_handler = ctrl_cmd_c;
	sigaction(SIGINT, &mini->new_c, &mini->old_c);
}
