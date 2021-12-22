/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 06:27:48 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/22 10:41:57 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

t_redir	*new_redir(t_redir *prev, char *word)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->next = NULL;
	prev->next = new;
	new->word = word;
	return (new);
}

t_cmd	*find_redir(t_cmd *cmd, char **argv)
{
	int y;

	y = -1;
	while (argv[++y])
	{
		if (!ft_strncmp((const char *)argv[y], INPUT, ft_strlen(argv[y])))
		{
			cmd->in = new_redir(cmd->in, argv[y + 1]);
			if (!cmd->in || !(cmd->in->word))
				return (0);
		}
		else if (!ft_strncmp((const char *)argv[y], OUTPUT, ft_strlen(argv[y])))
		{
			cmd->out = new_redir(cmd->out, argv[y + 1]);
			if (!cmd->out || !(cmd->out->word))
				return (0);
		}
		else if (!ft_strncmp((const char *)argv[y], HEREDOC, ft_strlen(argv[y])))
		{
			cmd->heredoc = new_redir(cmd->heredoc, argv[y + 1]);
			if (!cmd->heredoc || !(cmd->heredoc->word))
				return (0);
		}
		else if (!ft_strncmp((const char *)argv[y], D_OUTPUT, ft_strlen(argv[y])))
		{
			cmd->append = new_redir(cmd->append, argv[y + 1]);
			if (!cmd->append || !(cmd->append->word))
				return (0);
		}
	}
}