/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 06:27:48 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/18 12:28:28 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

t_redir	*new_redir(t_redir *prev, char *word, int type)
{
	t_redir	*new;

	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->prev = prev;
	new->next = NULL;
	prev->next = new;
	new->word = word;
	new->type = type;
	return (new);
}

static int	which_type(char *str)
{

	if (ft_strncmp(str, INPUT, ft_strlen(INPUT)) || \
		ft_strncmp(str, OUTPUT, ft_strlen(OUTPUT)))
		return (0);
	return (1);
	/*if (ft_strlen(str) > 1)
		return (1);
	return (0);*/
}

/*void	destroy_redir_from_cli(char **argv, int y)
{

	int	size;

	size = -1;
	while (argv[size])
		++size;
	free(argv[y]);
	free(argv[y + 1]);
	while (y + 2 <= size)
		argv[y] = argv[y + 2];
}*/

char *get_redir_word(char *str, int *i)
{
	int	end;
	char	*ret;

	end = 0;
	while (str[end] || ft_is_white_space(str[end]))
		++end;
	ret = ft_substr(str, 0, end);
	*i += end;
	return (ret);
}

t_cmd	*find_redir(t_cmd *cmd, char *cm)
{
	int	i;
	int	x;

	i = -1;
	x = -1;
	while (cm[++i])
	{
		if (cm[i] == '\'' || cm[i] == '\"')
			skip_quotes(cm, &i, cm[i]);
		else if (!ft_strncmp(&cm[i], INPUT, ft_strlen(INPUT)) || 
			!ft_strncmp(&cm[i], HEREDOC, ft_strlen(HEREDOC)))
		{
			x = i;
			cmd->in = new_redir(cmd->in, get_redir_word(&cm[x], &i), which_type(&cm[x]));
			if (!cmd->in || !(cmd->in->word))
				return (0);
			--x;
			while (++x < i)
				mv_str_left(&(cm[x]));
		}
		else if (!ft_strncmp(&cm[i], OUTPUT, ft_strlen(OUTPUT)) || 
			!ft_strncmp(&cm[i], D_OUTPUT, ft_strlen(D_OUTPUT)))
		{
			x = i;
			cmd->out = new_redir(cmd->out, get_redir_word(&cm[x], &i), which_type(&cm[x]));
			if (!cmd->out || !(cmd->out->word))
				return (0);
		}
	}
	/*while (argv[++y])
	{
		if (!ft_strncmp((const char *)argv[y], INPUT, ft_strlen(argv[y])) || 
			!ft_strncmp((const char *)argv[y], HEREDOC, ft_strlen(argv[y])))
		{
			cmd->in = new_redir(cmd->in, argv[y + 1], which_type(argv[y]));
			if (!cmd->in || !(cmd->in->word))
				return (0);
			destroy_redir_from_cli(argv, y);
			--y;
		}
		else if (!ft_strncmp((const char *)argv[y], OUTPUT, 
			ft_strlen(argv[y])) || !ft_strncmp((const char *)argv[y], D_OUTPUT, 
				ft_strlen(argv[y])))
		{
			cmd->out = new_redir(cmd->out, argv[y + 1], which_type(argv[y]));
			if (!cmd->out || !(cmd->out->word))
				return (0);
			destroy_redir_from_cli(argv, y);
			--y;
		}
	}*/
	return (cmd);
}