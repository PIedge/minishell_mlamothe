/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:08:03 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/26 20:57:52 by tmerrien         ###   ########.fr       */
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
		{
			mini->cmd = work;
			while (pipes[y])
				free(pipes[y++]);
			free(pipes);
			return (0);
		}
		work->cmd = pipes[y];
	}
	// Test Zone
	/*while (work->prev)
		work = work->prev;
	while (work->next)
	{
		printf("work->cmd |%s|\n", work->cmd);
		ft_printf_double_tab(work->cm_argv, "work->cm_argv");
		work = work->next;
		//work = work->next;
	}
	printf("work->cmd |%s|\n", work->cmd);
	ft_printf_double_tab(work->cm_argv, "work->cm_argv");*/
	// Test Zone
	while (work->prev)
		work = work->prev;
	mini->cmd = work;
	free(pipes);
	return (1);
}

int	var_treat_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cm_argv[i])
	{
		if (!var_treat_str(&(cmd->cm_argv[i]), g_env))
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
}

void	strip_quote_cmd(t_cmd *cmd)
{
	int	i;
	int	y;

	y = 0;
	while (cmd->cm_argv[y])
	{
		i = 0;
		while (cmd->cm_argv[y][i])
		{
			if (cmd->cm_argv[y][i] == '\'')
				until_same(cmd->cm_argv[y], &i);
			else if (cmd->cm_argv[y][i] == '"')
				until_same(cmd->cm_argv[y], &i);
			else
				++i;
		}
		++y;
	}
}

int	minishell(t_mini *mini)
{
	//printf("g : %s\n",g_env[31]);
	mini->cmd_ori = readline(PROMPT);
	//HISTORY
	add_history(mini->cmd_ori);
/*	mini->history = history_list();
	if (mini->history)
		return(printf("hist 0 : %s\n", mini->history));
	else
		return(printf("no_hist\n"));*/

	//printf("here\n");
	if (!(mini->cmd_ori) || !mini->cmd_ori[0])
		return (1);
	mini->cmd_ori = var_treat_str(&mini->cmd_ori, g_env);
	if (!mini->cmd_ori)
		return (0);
	//printf("after var treat |%s|\n", mini->cmd_ori);
	if (!set_pipes(mini))
		return (0);
	while (mini->cmd->next)
	{
		//if (!var_treat_cmd(mini->cmd, mini))
		//	return (0);
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
	t_cmd *work = mini->cmd;
	while (work->prev)
		work = work->prev;
	while (work->next)
	{
	//	printf("work->cmd |%s|\n", work->cmd);
	//	ft_printf_double_tab(work->cm_argv, "work->cm_argv");
		work = work->next;
		//work = work->next;
	}
	//printf("work->cmd |%s|\n", work->cmd);
	//ft_printf_double_tab(work->cm_argv, "work->cm_argv");
	//printf("out\n");
	//printf("\e[1;36mEXECUTION\e[0m\n");
	int nb;							//nb commands

	nb = 1;
	while(mini->cmd->prev && ++nb)
		mini->cmd = mini->cmd->prev;
	if (exec_cmd(mini->cmd, nb, mini))
	{
		select_err(mini->err);
	}
	return (1);
	// Test Zone
	// Execution
}
