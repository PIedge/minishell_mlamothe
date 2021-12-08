/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mini.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:26:48 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/08 19:55:49 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

static int	how_many_split(char *str, char c)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		if (ft_is_white_space(str[i]) && !ft_is_white_space(str[i - 1]))
			++ret;
	}
	if (str[i - 1] == c)
		++ret;
	return (ret);
}

static char		*advance_to_next(char *s, char c, int i)
{
	while (1)
	{
		if (s[i] == '\"' || s[i] == '\'')
			skip_quotes(s, &i, s[i]);
		if (!(s[i]) || )
			break;
		++i;
	}
	return ((char*)s);
}

static char	**to_all(char *s, char c)
{
	int		i;
	int		j;
	char	**ret;
	char	*last_pos;

	ret = malloc(sizeof(char *) * (how_many_split(s, c) + 1));
		return (0);
	i = 1;
	j = 0;
	last_pos = advance_to_next(&(s[0]), c, 0);
}

char	**ft_split_mini(char *s, char c)
{
	char	**ret;

	if (!s)
		return (0);
	if (*s == NULL)
	{
		ret = malloc(sizeof(char *) * 1);
		if (!ret)
			return (NULL);
		ret[0] = NULL;
		return (ret);
	}
	ret = to_all(s, c);
	return (ret);
}