/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_wp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:43:06 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/12 23:45:03 by tmerrien         ###   ########.fr       */
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
	while (str[++i])
	{
		if (str[i] == '\"' || str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		if (ft_is_white_space(str[i]) && !ft_is_white_space(str[i - 1]))
			++ret;
	}
	if (!ft_is_white_space(str[i - 1]))
		++ret;
	printf("how_many_split return %d\n", ret);
	return (ret);
}

static int	find_next_split(char *s, int *x)
{
	while (ft_is_white_space(s[*x]))
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

static char	**to_all(char *s, char **ret)
{
	int		x;
	int		y;
	int		start_split;

	x = 0;
	y = 0;
	start_split = find_next_split(s,&x);
	while (s[++x])
	{
		if (s[x] == '\'' || s[x] == '\"')
			skip_quotes(s, &x, s[x]);
		if (ft_is_white_space(s[x]) && !ft_is_white_space(s[x - 1]))
		{
			if (!free_if_wrong(ret, &(s[start_split]), &(s[x]), y++))
				return (0);
			start_split = find_next_split(s, &x);
		}
	}
	if (!ft_is_white_space(s[x - 1]) &&
		!free_if_wrong(ret, &(s[start_split]), &(s[x]), y++))
		return (0);
	ret[y] = 0;
	return (ret);
}


char	**ft_split_wp(char *s)
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
	ret = malloc(sizeof(char *) * (how_many_split(s) + 1));
	if (ret == NULL)
		return (0);
	to_all(s, ret);
	return (ret);
}