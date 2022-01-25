/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:41:15 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/25 11:46:31 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>
#include <unistd.h>

t_cmd	*create_cmd(t_cmd *prev)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (0);
	if (prev)
		prev->next = new;
	new->prev = prev;
	new->next = NULL;
	new->cm_argv = NULL;
	new->cmd = NULL;
	new->in = NULL;
	new->out = NULL;
	return (new);
}

t_redir	*create_redir(t_redir *prev, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (0);
	new->prev = prev;
	new->type = type;
	new->prev->next = NULL;
	new->word = NULL;
	return (new);
}

void	free_redir(t_redir *redir)
{
	while (redir && redir->next)
	{
		free(redir->word);
		redir = redir->next;
		free(redir->prev);
	}
	if (redir)
	{
		free(redir->word);
		free(redir);
	}
}

void	free_cmd(t_cmd *cmd)
{
	while (cmd && cmd->next)
	{
		ft_double_tab_free(cmd->cm_argv);
		free(cmd->cmd);
		free_redir(cmd->in);
		free_redir(cmd->out);
		cmd = cmd->next;
		free(cmd->prev);
	}
	if (cmd)
	{
		ft_double_tab_free(cmd->cm_argv);
		free(cmd->cmd);
		free_redir(cmd->in);
		free_redir(cmd->out);
		free(cmd);
	}
}

void	destroy(t_mini *mini, char *str)
{
	free_cmd(mini->cmd);
	ft_double_tab_free(mini->env);
	write(2, str, ft_strlen(str));
	exit(0);
}