/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 08:48:17 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/30 20:40:49 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft_re/libft_re.h"


int	init_mini(t_mini *mini, char **envp)
{
	mini->cmd = NULL;
	mini->env = envp;
}

void	minishell(t_mini *mini)
{
	char	*cmd_ori;

	cmd_ori = ft_readline(PROMPT);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	init_mini(&mini, envp);
	if (ac > 1)
		destroy(&mini)
}