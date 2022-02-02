/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/02 12:40:33 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <sys/types.h>
#include <signal.h>
#include <sys/ucontext.h>
#include <unistd.h>

void	cancel_sig(t_mini *mini, char val)
{
	if (val)
	{
		signal(SIGINT, SIG_DFL);
		return ;
	}
	signal(SIGINT, mini->new_c.sa_handler);
}

void	ctrl_c(int sig)
{
	//printf("\n%s", PROMPT);
	printf("\n");
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
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
	mini->new_c.sa_handler = ctrl_c;
	sigaction(SIGINT, &mini->new_c, &mini->old_c);
}
