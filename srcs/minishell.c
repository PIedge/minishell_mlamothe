/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:08:03 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/18 13:38:17 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

#include <stdio.h>

int	cm_argv_creation(t_cmd *work)
{
	work->cm_argv = ft_split_wp(work->cmd);
	if (!work->cm_argv)
		return (0);
	return (1);
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
			return (0);
		work->cmd = pipes[y];
		if (!cm_argv_creation(work))
			return (0);
	}
	// Test Zone
	while (work->prev)
		work = work->prev;
	while (work->next)
	{
		printf("work->cmd |%s|\n", work->cmd);
		ft_printf_double_tab(work->cm_argv, "work->cm_argv");
		//work = work->next;
	}
	printf("work->cmd |%s|\n", work->cmd);
	ft_printf_double_tab(work->cm_argv, "work->cm_argv");
	// Test Zone
	while (work->prev)
		work = work->prev;
	mini->cmd = work;
	return (1);
}

int	var_treat_cmd(t_cmd *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	while (cmd->cm_argv[i])
	{
		if (!var_treat_str(&(cmd->cm_argv[i]), g_env, mini))
			return (0);
		++i;
	}
	return (1);
}

void	until_same(char *str, int *i)
{
	char	c;

	c = str[(*i)];
	mv_str_left(&(str[*i]));
	while (str[*i] && str[*i] != c)
		++(*i);
	mv_str_left(&(str[*i]));
	--(*i);
}

void	strip_quote_cmd(t_cmd *cmd)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (cmd->cm_argv[y])
	{
		while (cmd->cm_argv[y][i])
		{
			if (cmd->cm_argv[y][i] == '\'')
				until_same(&(cmd->cm_argv[y][i]), &i);
			else if (cmd->cm_argv[y][i] == '"')
				until_same(&(cmd->cm_argv[y][i]), &i);
			else
				++i;
		}
		++y;
	}
}

int	minishell(t_mini *mini)
{
	mini->cmd_ori = ft_readline(PROMPT);
	if (!(mini->cmd_ori))
		return (0);
	var_treat_str(&mini->cmd_ori, g_env, mini);
	if (!set_pipes(mini))
		return (0);
	while (mini->cmd->next)
	{
		//if (!var_treat_cmd(mini->cmd, mini))
		//	return (0);
		if (!find_redir(mini->cmd, *mini->cmd->cm_argv))
			return (0);
		strip_quote_cmd(mini->cmd);
		mini->cmd = mini->cmd->next;
	}
	if (!find_redir(mini->cmd, *mini->cmd->cm_argv))
			return (0);
	strip_quote_cmd(mini->cmd);
	// Test Zone
	/*int	y = 0;
	while (mini->cmd->next)
	{
		y = 0;
		while (mini->cmd->cm_argv[y])
			printf("%s\n", mini->cmd->cm_argv[y++]);
		mini->cmd = mini->cmd->next;
	}
	y = 0;
	while (mini->cmd->cm_argv[y])
		printf("%s\n", mini->cmd->cm_argv[y++]);*/
	printf("out\n");
	return (1);
	// Test Zone
	// Execution
}
