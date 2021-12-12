/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:41:15 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/12 17:22:29 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

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
	new->redir = NULL;
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
	while (redir->next)
	{
		free(redir->word);
		redir = redir->next;
		free(redir->prev);
	}
	free(redir->word);
	free(redir);
}

void	free_cmd(t_cmd *cmd)
{
	while (cmd->next)
	{
		ft_double_tab_free(cmd->cm_argv);
		free(cmd->cmd);
		free_redir(cmd->redir);
		cmd = cmd->next;
	}
	ft_double_tab_free(cmd->cm_argv);
	free(cmd->cmd);
	free_redir(cmd->redir);
}

void	destroy(t_mini *mini)
{
	free_cmd(mini->cmd);

	
}