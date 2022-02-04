/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:08:03 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 13:34:42 by tmerrien         ###   ########.fr       */
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

int	minishell(t_mini *mini)
{
	int	retexec;
	int	nb;

	mini->cmd_ori = readline(PROMPT);
	eof_in_cmd(mini);
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
