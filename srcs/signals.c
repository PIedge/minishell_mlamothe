/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/31 06:58:25 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <sys/types.h>
#include <signal.h>
#include <sys/ucontext.h>
#include <unistd.h>

void	init_signals()
{
	struct sigaction	control_c;
	struct sigaction	control_d;
	struct sigaction	control_back;
	
}

void	ctrl_c(int sig)
{
	
	
}