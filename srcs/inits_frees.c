/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_frees.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:41:15 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/30 10:01:53 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"


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
	}
}

void	destroy(t_mini *mini)
{
	free_cmd(mini->cmd);

}