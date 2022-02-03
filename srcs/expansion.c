/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:45:59 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 17:22:12 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_re/libft_re.h"
#include "../includes/minishell.h"
#include <stdlib.h>

#include <stdio.h>

int	is_variable_name_valid(char *s)
{
	int	i;

	i = 0;
	while (!ft_is_white_space(s[++i]))
	{
		if (i == 1)
		{
			if (!ft_isalpha(s[i]) && s[i] != '_')
				return (0);
		}
		else if (i > 0)
		{
			if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]))
				return (0);
		}
	}
	return (1);
}

int	calc_new_len(char *str, char **env, int *n)
{
	int		i;
	int		end;
	int		len;
	char	*var;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		else if (str[i] == '$')
		{
			++i;
			end = get_end_index(&(str[i])) + i;
			var = find_var_with_limit(env, &str[i], &str[end]);
			len += ft_strlen(var);
			*n += 1;
			if (str[i] == '?')
				free(var);
		}
		else
			norm_new_len(&len, &i);
	}
	return (len);
}

int	copy_var_into_new(char *ori, char *new, char **env, int *y)
{
	int		end;
	char	*var;
	int		o;
	int		i;
	int		a;

	o = 0;
	i = 0;
	end = 0;
	a = 0;
	if (ori[i] == '$')
	{
		end = get_end_index(&(ori[i])) + i;
		var = find_var_with_limit(env, &ori[i + 1], &ori[end]);
		if (!var)
			return (end);
		norm_copy_var_into_new(ori, var, &a, i);
		ft_strcpy(new, &var[a]);
		*y += ft_strlen(&var[a]);
		if (ori[i + 1] == '?')
			free(var);
	}
	return (end);
}

char	*var_treat_str(char **str, char **env)
{
	int		new_len;
	int		i;
	int		y;
	char	*new;

	i = 0;
	y = 0;
	new_len = 0;
	if (!need_to_add(*str, env, &new_len))
		return (*str);
	if (!norm_vts(&new, new_len))
		return (0);
	while ((*str)[i])
	{
		copy_until_var(*str, new, &i, &y);
		if ((*str)[i] == '$')
			i += copy_var_into_new(&((*str)[i]), &(new[y]), env, &y);
		else if ((*str)[i])
			++i;
	}
	new[y] = '\0';
	free(*str);
	*str = new;
	return (new);
}
