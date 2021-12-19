/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 08:48:17 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/19 06:21:50 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft_re/libft_re.h"


int	init_mini(t_mini *mini, char **envp)
{
	int	i;

	i = 0;
	mini->cmd = NULL;
	mini->env = copy_env(envp);
	if (!(mini->env))
		return (0);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	av = 0;
	if (!init_mini(&mini, envp))
		destroy(&mini, E_MALLOC);
	// if (ac > 1)
		// destroy(&mini);
	/*
	** This main isn't finished, basicaly serves for test cases rn, you know what that means
	** TEST ZONE START
	*/
	minishell(&mini);
	/*
	** TEST ZONE END
	*/
	return (1);
}