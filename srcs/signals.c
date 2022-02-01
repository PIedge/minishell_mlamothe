/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/01 11:46:50 by tmerrien         ###   ########.fr       */
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
	struct sigaction	sig_c;
	struct sigaction	sig_back;

	ft_memset((void *)&sig_c, sizeof(sig_c));
	ft_memset((void *)&sig_back, sizeof(sig_back));
	sig_c.sa_handler = ctrl_c;
	sig_back.sa_handler = ctrl_back;
	sigaction(SIGINT, &sig_c, &mini->old_c);
	sigaction(SIGQUIT, &sig_back, &mini->old_bs);
		
}
