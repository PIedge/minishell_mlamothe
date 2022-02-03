/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 06:27:48 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 15:10:42 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

#include <stdio.h>

t_redir	*new_redir(t_redir *prev, char *word, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->next = NULL;
	new->word = word;
	new->type = type;
	if (prev)
		prev->next = new;
	return (new);
}

static int	which_type(char *str)
{
	if (!ft_strncmp(str, HEREDOC, ft_strlen(HEREDOC)) || \
		!ft_strncmp(str, D_OUTPUT, ft_strlen(D_OUTPUT)))
		return (1);
	return (0);
}

char	*get_redir_word(char *str, int *i)
{
	int		end;
	int		start;
	char	*ret;

	start = 0;
	while (str[start] && (str[start] == '<' || str[start] == '>'))
		++start;
	while (str[start] && ft_is_white_space(str[start]))
		++start;
	end = start;
	while (str[end] && !ft_is_white_space(str[end]))
		++end;
	ret = ft_substr(str, start, end - start);
	*i += end;
	return (ret);
}

int	in_if_find_redir(t_cmd *cmd, char *cm, t_mini *mini, int *i)
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

t_cmd	*find_redir(t_cmd *cmd, char *cm, t_mini *mini)
{
	int		i;
	int		x;
	int		stand;

	(void)mini;
	i = 0;
	x = -1;
	while (cm[i])
	{
		if (cm[i] == '\'' || cm[i] == '\"')
			skip_quotes(cm, &i, cm[i]);
		else if (!ft_strncmp(&cm[i], INPUT, ft_strlen(INPUT)) || \
			!ft_strncmp(&cm[i], HEREDOC, ft_strlen(HEREDOC)))
		{
			
			/*x = i;
			cmd->in = new_redir(cmd->in, get_redir_word(&cm[x], &i), \
				which_type(&cm[x]));
			if (!cmd->in || !(cmd->in->word))
				return (0);
			stand = x;
			while (++x <= i)
				mv_str_left(&(cm[stand]));
			i = stand;*/
		}
		else if (!ft_strncmp(&cm[i], OUTPUT, ft_strlen(OUTPUT)) || \
			!ft_strncmp(&cm[i], D_OUTPUT, ft_strlen(D_OUTPUT)))
		{
			x = i;
			cmd->out = new_redir(cmd->out, get_redir_word(&cm[x], &i), \
				which_type(&cm[x]));
			if (!cmd->out || !(cmd->out->word))
				return (0);
			stand = x;
			while (++x <= i)
				mv_str_left(&(cm[stand]));
		}
		else
			++i;
	}
	return (cmd);
}
