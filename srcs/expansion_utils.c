/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 16:15:47 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 10:48:40 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_re/libft_re.h"
#include "../includes/minishell.h"
#include <stdlib.h>

void	norm_new_len(int *len, int *i)
{
	++(*len);
	++(*i);
}

void	norm_copy_var_into_new(char *ori, char *var, int *a, int i)
{
	while (ori[i + 1] != '?' && var[*a] != '=')
		++(*a);
	if (var[*a] == '=')
		++(*a);
}

char	*norm_vts(char **new, int n_len)
{
	*new = malloc(sizeof(char) * (n_len + 1));
	if (!(*new))
		return (0);
	ft_bzero((void *)*new, n_len);
	return (*new);
}

void	copy_until_var(char *ori, char *new, int *i, int *y)
{
	int	quote;

	quote = 0;
	while (ori[*i] && (ori[*i] != '$' || quote))
	{
		if (ori[*i] == '\'')
		{
			if (quote == 0)
				quote = 1;
			else
				quote = 0;
		}
		new[*y] = ori[*i];
		++(*i);
		++(*y);
	}
	if (ori[*i] == '\0')
		new[*y] = ori[*i];
}

int	need_to_add(char *str, char **env, int *n_len)
{
	int	n;

	n = 0;
	*n_len = calc_new_len(str, env, &n);
	return (n);
}
