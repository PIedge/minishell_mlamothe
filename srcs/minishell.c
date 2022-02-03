/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:08:03 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 14:41:36 by tmerrien         ###   ########.fr       */
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
	while (work->prev)
		work = work->prev;
	mini->cmd = work;
	free(pipes);
	return (1);
}

int	var_treat_cmd(t_cmd *cmd, t_mini *mini)
{
	int	i;

	i = 0;
	while (cmd->cm_argv[i])
	{
		if (!var_treat_str(&(cmd->cm_argv[i]), mini->env))
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
	int ret;
	t_cmd *work;

	ret = 1;
	work = mini->cmd;	
	while (work->prev)
		work = work->prev;
	while (work->next)
		work = work->next;
	while(mini->cmd->prev && ++ret)
		mini->cmd = mini->cmd->prev;
	return (ret);
}

int	minishell(t_mini *mini)
{
	int retexec;
	int	nb;

	mini->cmd_ori = readline(PROMPT);
	EOF_in_cmd(mini);
	add_history(mini->cmd_ori);
	if (!(mini->cmd_ori) || !mini->cmd_ori[0])
		return (1);
	if (!parse_some_things(mini))
		return (1);
	nb = how_much_cmd(mini);
	retexec = exec_cmd(mini->cmd, nb, mini);
	if (retexec == 0)
	{
		rl_clear_history();
		return (0);
	}
	if (retexec == 2)
		select_err(mini->err, mini->err_word);
	sigaction(SIGINT, &mini->new_c, NULL);
	return (1);
}
