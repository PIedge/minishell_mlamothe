/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:26:48 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/12 18:42:06 by tmerrien         ###   ########.fr       */
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

	i = 0;
	ret = 0;
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		if (str[i] == c && str[i - 1] != c)
			++ret;
	}
	if (str[i - 1] != c)
		++ret;
	return (ret);
}

static int	find_next_split(char *s, char c, int *x)
{
	while (s[*x] == c)
		++(*x);
	return (*x);
}

static int		free_if_wrong(char **ret, char *s, char *actual, int y)
{
	ret[y] = ft_substr(s, 0, actual - s);
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

static char	**to_all(char *s, char c)
{
	int		x;
	int		y;
	int		start_split;
	char	**ret;

	ret = malloc(sizeof(char *) * (how_many_split(s, c) + 1));
	if (ret == NULL)
		return (0);
	x = 0;
	y = 0;
	start_split = find_next_split(s, c, &x);
	while (s[++x])
	{
		if (s[x] == '\'' || s[x] == '\"')
			skip_quotes(s, &x, s[x]);
		if (s[x] == c && s[x - 1] != c)
		{
			if (!free_if_wrong(ret, &(s[start_split]), &(s[x]), y++))
				return (0);
			start_split = find_next_split(s, c, &x);
		}
	}
	if (s[x - 1] != c && !free_if_wrong(ret, &(s[start_split]), &(s[x]), y++))
		return (0);
	ret[y] = 0;
	return (ret);
}

char	**ft_split_pipes(char *s, char c)
{
	char	**ret;

	if (!s)
		return (0);
	if (*s == '\0')
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