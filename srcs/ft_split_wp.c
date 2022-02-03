/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:43:06 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 17:58:42 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

#include <stdio.h>

static int	how_many_split(char *str)
{
	int	ret;
	int	i;

	i = 0;
	ret = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		else if (ft_is_white_space(str[i]))
		{
			while (ft_is_white_space(str[i]))
				++i;
			++ret;
		}
		else
			++i;
	}
	if (!ft_is_white_space(str[i - 1]))
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

static int	find_start_split(char *str, int i, int *truc)
{
	while (str[i] && ft_is_white_space(str[i]))
		++i;
	*truc = i;
	return (i);
}

static char	**to_all(char *s, char **ret, int *start)
{
	int		x;
	int		y;

	y = 0;
	x = find_start_split(s, 0, start);
	while (s[x])
	{
		if (s[x] == '\'' || s[x] == '\"')
			skip_quotes(s, &x, s[x]);
		else if (ft_is_white_space(s[x]))
		{
			if (!free_if_wrong(ret, &(s[x]), &(s[*start]), y++))
				return (0);
			x = find_start_split(s, x, start);
		}
		else
			++x;
	}
	if (!ft_is_white_space(s[x - 1]) && \
		!free_if_wrong(ret, &s[x], &s[*start], y++))
		return (0);
	ret[y] = 0;
	return (ret);
}

char	**ft_split_wp(char *s)
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
	ret = malloc(sizeof(char *) * (how_many_split(s) + 1));
	if (ret == NULL)
		return (0);
	to_all(s, ret, &start);
	return (ret);
}
