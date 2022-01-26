/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 06:27:48 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/26 01:36:21 by mlamothe         ###   ########.fr       */
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
	printf("type new_redir %d\n", type);
	new->type = type;
	if (prev)
		prev->next = new;
	return (new);
}

static int	which_type(char *str)
{
	printf("which_type |%s| %d %d\n", str, ft_strncmp(str, INPUT, ft_strlen(INPUT)), ft_strncmp(str, INPUT, ft_strlen(OUTPUT)));
	if (!ft_strncmp(str, HEREDOC, ft_strlen(HEREDOC)) || 
		!ft_strncmp(str, D_OUTPUT, ft_strlen(D_OUTPUT)))
		return (1);
	return (0);
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
	int	start;
	char	*ret;

	start = 0;
	while (str[start] && (str[start] == '<' || str[start] == '>'))
		++start;
	while (str[start] && ft_is_white_space(str[start]))
		++start;
	end = start;
	while (str[end] && !ft_is_white_space(str[end]))
		++end;
	//printf("start %d end %d moins %d\n", start, end, end - start);
	ret = ft_substr(str, start, end - start);
	*i += end;
	return (ret);
}

t_cmd	*find_redir(t_cmd *cmd, char *cm)
{
	int	i;
	int	x;
	int	stand;

	i = 0;
	x = -1;
	printf("\nENTERING FIND REDIR\n");
	printf("cmd treated |%s|\n", cm);
	while (cm[i])
	{
		printf("char looked at find_redir |%c|\n", cm[i]);
		if (cm[i] == '\'' || cm[i] == '\"')
			skip_quotes(cm, &i, cm[i]);
		else if (!ft_strncmp(&cm[i], INPUT, ft_strlen(INPUT)) || 
			!ft_strncmp(&cm[i], HEREDOC, ft_strlen(HEREDOC)))
		{
			printf("here\n");
			x = i;
			if (which_type(&cm[x]))																						//HEREDOC
				cmd->in = new_redir(cmd->in, ft_here_doc(get_redir_word(&cm[x], &i), x), which_type(&cm[x]));
			else
				cmd->in = new_redir(cmd->in, get_redir_word(&cm[x], &i), which_type(&cm[x]));
			if (!cmd->in || !(cmd->in->word))
				return (0);
			stand = x;
			while (++x <= i)
				mv_str_left(&(cm[stand]));
			i = stand;
		}
		else if (!ft_strncmp(&cm[i], OUTPUT, ft_strlen(OUTPUT)) || 
			!ft_strncmp(&cm[i], D_OUTPUT, ft_strlen(D_OUTPUT)))
		{
			printf("la\n");
			x = i;
			cmd->out = new_redir(cmd->out, get_redir_word(&cm[x], &i), which_type(&cm[x]));
			if (!cmd->out || !(cmd->out->word))
				return (0);
			stand = x;
			while (++x <= i)
				mv_str_left(&(cm[stand]));
		}
		else
			++i;
	}
	printf("end\n");
	// TEST ZONE
	// while (cmd->in && cmd->in->prev)
	// 	cmd->in = cmd->in->prev;
	// while (cmd->out && cmd->out->prev)
	// 	cmd->out = cmd->out->prev;
	// while (cmd->in && cmd->in->next)
	// {
	// 	printf("cmd->in |%s| %d\n", cmd->in->word, cmd->in->type);
	// 	cmd->in = cmd->in->next;
	// }
	// if (cmd->in)
	// 	printf("cmd->in |%s| %d\n", cmd->in->word, cmd->in->type);
	// while (cmd->out && cmd->out->next)
	// {
	// 	printf("cmd->out |%s| %d\n", cmd->out->word, cmd->out->type);
	// 	cmd->out = cmd->out->next;
	// }
	// if (cmd->out)
	// 	printf("cmd->out |%s| %d\n", cmd->out->word, cmd->out->type);
	// END TEST ZONE
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