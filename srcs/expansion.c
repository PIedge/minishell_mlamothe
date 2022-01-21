/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:45:59 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/21 07:06:40 by tmerrien         ###   ########.fr       */
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

int	get_end_index(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_is_white_space(str[i]) && str[i] != '"')
		++i;
	return (i);
}

int	calc_new_len(char *str, char **env, int *n)
{
	int	i;
	int	end;
	int	len;

	i = 0;
	len = 0;
	printf("calc_new_len |%s|\n", str);
	while (str[i])
	{
		printf("char looked at |%c|\n", str[i]);
		if (str[i] == '\'')
			skip_quotes(str, &i, str[i]);
		else if (str[i] == '$')
		{
			++i;
			end = get_end_index(&(str[i])) + i;
			printf("char looked at |%c|\n", str[end]);
			printf("calc_new_len |%s|\n", find_var_with_limit(env, &str[i], &str[end]));
			len += ft_strlen(find_var_with_limit(env, &str[i], &str[end]));
			*n += 1;
		}
		else
			++i;
		
	}
	return (len);
}

void	copy_until_var(char *ori, char *new, int *i, int *y)
{
	int	quote;

	quote = 0;
	while (ori[*i] && (ori[*i] != '$' || quote))
	{
		printf("char looked at |%c|\n", ori[*i]);
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
	printf("char looked at |%c|\n", ori[*i]);
}

int	copy_var_into_new(char *ori, char *new, char **env, int *y)
{
	int	end;
	char	*var;
	int	o;
	int	i;
	//int	quote;

	o = 0;
	i = 0;
	end = 0;
	if (ori[i] == '$')
	{
		end = get_end_index(&(ori[i])) + i;
		var = find_var_with_limit(env, &ori[i + 1], &ori[end]);
		if (!var)
			return (end);
		ft_strcpy(new, var);
		*y += ft_strlen(var);
	}
	return (end);
}

char	*var_treat_str(char **str, char **env)
{
	int	new_len;
	int	i;
	int	y;
	char	*new;
	int	n;

	i = 0;
	y = 0;
	n = 0;
	printf("not dead var_treat_str\n");
	new_len = calc_new_len(*str, env, &n);
	if (n == 0)
		return (*str);
	new = malloc(sizeof(char) * (new_len + 1));
	if (!new)
		return (0);
	ft_bzero((void *)new, new_len);
	while ((*str)[i])
	{
		copy_until_var(*str, new, &i, &y);
		if ((*str)[i] == '$')
			i += copy_var_into_new(&((*str)[i]), new, env, &y);
		else
			++i;
	}
	new[y] = '\0';
	printf("%p new\n", new);
	free(*str);
	*str = new;
	return (new);
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