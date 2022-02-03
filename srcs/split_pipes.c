/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:26:48 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 22:32:40 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

#include <stdio.h>

static int	how_many_split(char *str, char c)
{
	int	ret;
	int	i;

	ret = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		else if (str[i] == c)
		{
			while (str[i] == c)
				++i;
			++ret;
		}
		else
			++i;
	}
	if (str[i - 1] != c)
		++ret;
	return (ret);
}

static int	free_if_wrong(char **ret, char *p_actual, char *p_start, int y)
{
	ret[y] = ft_substr(p_start, 0, p_actual - p_start);
	if (!(ret[y]))
	{
		while (y >= 0)
			free(ret[y--]);
		free(ret);
		ret = 0;
		return (0);
	}
	return (1);
}

int	find_start_split(char *str, int i, char c, int *start)
{
	while (str[i] && str[i] == c)
		++i;
	*start = i;
	return (i);
}

static char	**to_all(char **ret, char *s, char c, int *start)
{
	int		x;
	int		y;

	y = 0;
	x = find_start_split(s, 0, c, start);
	while (s[x])
	{
		if (s[x] == '\'' || s[x] == '\"')
			skip_quotes(s, &x, s[x]);
		else if (s[x] == c)
		{
			if (!free_if_wrong(ret, &s[x], &s[*start], y++))
				return (0);
			x = find_start_split(s, x, c, start);
		}
		else
			++x;
	}
	if (s[x - 1] != c && !free_if_wrong(ret, &s[x], &s[*start], y++))
		return (0);
	ret[y] = 0;
	return (ret);
}

char	**ft_split_pipes(char *s, char c)
{
	char	**ret;
	int		start;

	if (!s)
		return (0);
	start = 0;
	if (*s == '\0')
	{
		ret = malloc(sizeof(char *) * 1);
		if (!ret)
			return (NULL);
		ret[0] = NULL;
		return (ret);
	}
	ret = malloc(sizeof(char *) * (how_many_split(s, c) + 1));
	if (ret == NULL)
		return (0);
	to_all(ret, s, c, &start);
	return (ret);
}
