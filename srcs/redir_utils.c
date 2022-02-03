/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 15:23:50 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 15:25:28 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

static int	which_type(char *str)
{
	if (!ft_strncmp(str, HEREDOC, ft_strlen(HEREDOC)) || \
		!ft_strncmp(str, D_OUTPUT, ft_strlen(D_OUTPUT)))
		return (1);
	return (0);
}

int	in_if_find_redir(t_cmd *cmd, char *cm, int *i)
{
	int	x;
	int	stand;

	x = *i;
	cmd->in = new_redir(cmd->in, get_redir_word(&cm[x], i), \
	which_type(&cm[x]));
	if (!cmd->in || !(cmd->in->word))
		return (0);
	stand = x;
	while (++x <= *i)
		mv_str_left(&(cm[stand]));
	*i = stand;
	return (1);
}

int	out_if_find_redir(t_cmd *cmd, char *cm, int *i)
{
	int	x;
	int	stand;

	x = *i;
	cmd->out = new_redir(cmd->out, get_redir_word(&cm[x], i), \
	which_type(&cm[x]));
	if (!cmd->out || !(cmd->out->word))
		return (0);
	stand = x;
	while (++x <= *i)
		mv_str_left(&(cm[stand]));
	return (1);
}
