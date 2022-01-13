/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:08:03 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/13 14:56:18 by tmerrien         ###   ########.fr       */
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
		work->cm_argv = ft_split_wp(work->cmd);
	}
	// Test Zone
	while (work->prev)
		work = work->prev;
	while (work)
	{
		printf("work->cmd |%s|\n", work->cmd);
		ft_printf_double_tab(work->cm_argv, "work->cm_argv");
		work = work->next;
	}
	// Test Zone
	return (1);
}

int	var_treat_cmd(t_cmd *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	while (cmd->cm_argv[i])
	{
		if (!var_treat_str(cmd->cm_argv[i], mini->env, mini))
			return (0);
		++i;
	}
	return (1);
}

int	minishell(t_mini *mini)
{
	mini->cmd_ori = ft_readline(PROMPT);
	if (!(mini->cmd_ori))
		return (0);
	if (!set_pipes(mini))
		return (0);
	while (mini->cmd->next)
	{
		if (!var_treat_cmd(mini->cmd, mini))
			return (0);
		if (!find_redir(mini->cmd, mini->cmd->cm_argv))
			return (0);
		
	}
	// Test Zone
	printf("out\n");
	return (1);
	// Test Zone
}
