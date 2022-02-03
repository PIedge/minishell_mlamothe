/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 22:13:33 by tmerrien         ###   ########.fr       */
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
	ft_memset((void *)&mini->new_c, sizeof(mini->new_c));
	ft_memset((void *)&mini->new_exec_c, sizeof(mini->new_exec_c));
	ft_memset((void *)&mini->lol, sizeof(mini->lol));
	mini->new_c.sa_handler = ctrl_c;
	mini->lol.sa_handler = ctrl_cmd_c;
	sigaction(SIGINT, &mini->new_c, &mini->old_c);
}
