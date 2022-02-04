/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 14:49:23 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 10:48:27 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	parse_some_things(t_mini *mini)
{
	mini->cmd_ori = var_treat_str(&mini->cmd_ori, mini->env);
	mini->err = 0;
	g_lrest = 0;
	if (!mini->cmd_ori)
		return (0);
	if (!set_pipes(mini))
		return (0);
	while (mini->cmd->next)
	{
		if (!find_redir(mini->cmd, mini->cmd->cmd, mini))
			return (0);
		if (!cm_argv_creation(mini->cmd))
			return (0);
		strip_quote_cmd(mini->cmd);
		mini->cmd = mini->cmd->next;
	}
	if (!find_redir(mini->cmd, mini->cmd->cmd, mini))
		return (0);
	if (!cm_argv_creation(mini->cmd))
		return (0);
	strip_quote_cmd(mini->cmd);
	return (1);
}

int	how_much_cmd(t_mini *mini)
{
	int		ret;
	t_cmd	*work;

	ret = 1;
	work = mini->cmd;
	while (work->prev)
		work = work->prev;
	while (work->next)
		work = work->next;
	while (mini->cmd->prev && ++ret)
		mini->cmd = mini->cmd->prev;
	return (ret);
}

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
		if (!work)
		{
			mini->cmd = work;
			ft_double_tab_free(pipes);
			return (0);
		}
		work->cmd = pipes[y];
	}
	while (work->prev)
		work = work->prev;
	mini->cmd = work;
	free(pipes);
	return (1);
}
