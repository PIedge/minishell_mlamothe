/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:08:03 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/12 18:42:13 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

#include <stdio.h>

int	set_pipes(t_mini *mini)
{
	t_cmd	*work;
	char	**pipes;
	int		y;

	pipes = ft_split_pipes(mini->cmd_ori, '|');
	if (!pipes)
		return (0);
	y = -1;
	work = NULL;
	while (pipes[++y])
	{
		work = create_cmd(work);
		work->cmd = pipes[y];
	}
	// Test Zone
	while (work->prev)
		work = work->prev;
	while (work)
	{
		printf("work->cmd |%s|\n", work->cmd);
		work = work->next;
	}
	// Test Zone
	return (1);
}

int	minishell(t_mini *mini)
{
	mini->cmd_ori = ft_readline(PROMPT);
	if (!(mini->cmd_ori))
		return (0);
	if (!set_pipes(mini))
		return (0);
	// Test Zone
	printf("out\n");
	return (1);
	// Test Zone
}