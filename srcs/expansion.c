/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:45:59 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/29 21:40:12 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_re/libft_re.h"
#include "../includes/minishell.h"

int	is_variable_name_valid(char *s)
{
	int	i;

	i = 0;
	while (!ft_is_white_space(s[++i]))
	{
		if (i == 1)
			if (!ft_isalpha(s[i]) && s[i] != '_')
				return (0);
		else if (i > 0)
			if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]))
				return (0);
	}
	return (1);
}



/*int	calc_vars_len(t_mini *mini, char *s, int *len_add, int *len_var_name)
{
	char	*var;
	int	i;

	i = -1;
	while (!(ft_is_white_space(s[++i])))
		++(*len_var_name);
	var = find_var();
	if (!var)
		return (-1);
	return (i);
}

int	is_variable_name_valid(char *s)
{
	int	i;

	i = 0;
	while (!ft_is_white_space(s[++i]))
	{
		if (i == 1)
			if (!ft_isalpha(s[i]) && s[i] != '_')
				return (0);
		else if (i > 0)
			if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]))
				return (0);
	}
	return (1);
}

int	how_much_space_needed(char *s)
{
	int	ini_len;
	int	len_add;
	int	len_var_name;
	int	i;
	int	ret;

	ini_len = (int)ft_strlen(s);
	i = 0;
	len_add = 0;
	len_var_name = 0;
	while (++i)
	{
		if (s[i] == '$' && is_variable_name_valid(&(s[i])))
		{
			ret = calc_vars_len(s, &i, &len_add, &len_var_name);
			if (ret < 0)
				return (-1);
		}
	}
}

char	*vars_treat(char *str, t_mini *mini)
{
	char	*new;
	int	size_more;

	size_more = how_much_space_needed(str);
}

////////////////////////////////////////////////////////////////
int	var_treat(char **str, int *i, t_mini *mini)
{
	int		end;
	char	*new;
	char	*var_name;
	char	*var_value;

	
	ft_str_shift_left(*str, 1, *i);
	if (!check_valid_var(str, i, 0))
		return (1);	
	end = check_valid_var(str, i, 1);
	if (!(var_name = ft_substr(*str, *i, end - *i)))
		return (0);
	if (var_name[0] == '?')
	{
		if (!(var_value = ft_itoa(g_last_return)))
			return (0);
	}
	else if (!(var_value = search_var(var_name)))
		return (0);
	if (!(new = malloc(sizeof(char) * (ft_strlen(*str) +
		ft_strlen(var_value) + 1))))
		return (0);
	ft_bzero(new, (ft_strlen(*str) + ft_strlen(var_value) + 1));
	ft_memcpy(new, *str, (size_t)(*i));
	ft_memcpy(new + *i, var_value, ft_strlen(var_value));
	if (ft_strlen(*str) + ft_strlen(var_value) > (size_t)end)
	{
		ft_memcpy(new + *i + (int)ft_strlen(var_value),
			&(*str)[end], ft_strlen(&(*str)[end]));
		*i = end;
	}
	free(*str);
	*str = new;
	free(var_value);
	return (1);
}*/
////////////////////////////////////////////////////////////////