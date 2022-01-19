/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 05:26:48 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/19 13:55:48 by tmerrien         ###   ########.fr       */
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
		if (str[i] == c)
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

/*static int	find_next_split(char *s, char c, int *x)
{
	while (s[*x] && s[*x] == c)
		++(*x);
	return (*x);
}*/

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

/*static int		free_if_wrong(char **ret, char *s, char *actual, int y)
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
}*/

int	find_start_split(char *str, int i, char c)
{
	while (str[i] && str[i] == c)
		++i;
	return (i);
}

static char	**to_all(char *s, char c)
{
	int		x;
	int		y;
	char	**ret;
	int	start;

	ret = malloc(sizeof(char *) * (how_many_split(s, c) + 1));
	if (ret == NULL)
		return (0);
	y = 0;
	start = find_start_split(s, 0, c);
	x = start;
	while (s[x])
	{
		if (s[x] == '\'' || s[x] == '\"')
			skip_quotes(s, &x, s[x]);
		if (s[x] == c)
		{
			if (!free_if_wrong(ret, &s[x], &s[start], y++))
				return (0);
			start = find_start_split(s, x, c);
			x = start;
		}
		else
			++x;
	}
	if (s[x - 1] != c && !free_if_wrong(ret, &s[x], &s[start], y++))
		return (0);
	ret[y] = 0;
	return (ret);
	/*start_split = find_next_split(s, c, &x);
	while (s[++x])
	{
		if (s[x] == '\'' || s[x] == '\"')
			skip_quotes(s, &x, s[x]);
		if (x == 0)
			++x;
		if (s[x] == c && s[x - 1] != c)
		{
			if (!free_if_wrong(ret, &(s[start_split]), &(s[x]), y++))
				return (0);
			printf("dead\n");
			start_split = find_next_split(s, c, &x);
		}
	}
	if (s[x - 1] != c && !free_if_wrong(ret, &(s[start_split]), &(s[x]), y++))
		return (0);
	ret[y] = 0;*/
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