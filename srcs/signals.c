/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/31 15:35:00 by tmerrien         ###   ########.fr       */
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
	printf("\n%s", PROMPT);
	sig = 0;
	g_lrest = 130;
}

void	ctrl_d(int sig)
{
	g_lrest = 0;
	sig = 0;

}

void	ctrl_back(int sig)
{
	sig = 0;
	printf("\b\b");
	g_lrest = 0;
}

void	init_signals(void)
{
	struct sigaction	sig_c;
	// struct sigaction	sig_d;
	struct sigaction	sig_back;

	ft_memset((void *)&sig_c, sizeof(sig_c));
	// ft_memset((void *)&sig_d, sizeof(sig_d));
	ft_memset((void *)&sig_back, sizeof(sig_back));
	sig_c.sa_handler = ctrl_c;
	// sig_d.sa_handler = ctrl_d;
	sig_back.sa_handler = ctrl_back;
	sigaction(SIGINT, &sig_c, 0);
	// sigaction(SIGQUIT, &sig_d, 0);
	// sigaction(SIGQUIT, &sig_back, 0);

}
