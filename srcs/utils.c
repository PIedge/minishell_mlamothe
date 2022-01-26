/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 12:23:31 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 12:06:30 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (1);
		++i;
	}
	if (s1[i] || s2[i])
		return (1);
	return (0);
}

char	*ft_join_cmd(char *str1, char *str2)
{
		int		i;
		int		j;
		char	*str_ret;

		if (str1[ft_strlen(str1) - 1] != '/')
			str_ret = malloc((ft_strlen(str1) + ft_strlen(str2) + 2) * sizeof(char));
		else
			str_ret = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
		if (!str_ret)
			return (NULL);
		i = -1;
		while (++i < (int)ft_strlen(str1))
			str_ret[i] = str1[i];
		j = -1;
		if (str1[ft_strlen(str1) - 1] != '/')
			str_ret[i++] = '/';
		while (++j < (int)ft_strlen(str2))
				str_ret[i + j] = str2[j];
		str_ret[i + j] = 0;
		return (str_ret);
}

char	*ft_join(char *str1, char *str2)
{
		int		i;
		int		j;
		char	*str_ret;

		str_ret = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
		if (!str_ret)
			return (NULL);
		i = -1;
		while (++i < (int)ft_strlen(str1))
			str_ret[i] = str1[i];
		j = -1;
		while (++j < (int)ft_strlen(str2))
				str_ret[i + j] = str2[j];
		str_ret[i + j] = 0;
		return (str_ret);
}

char	*ft_strdup(const char *src)
{
		int			 i;
		char	*res;

		i = -1;
		res = malloc((ft_strlen((char *)src) + 1) * sizeof(char));
		if (!(res))
				return (NULL);
		while (src[++i])
				res[i] = src[i];
		res[i] = 0;
		return (res);
}

int	get_var_name_end(char *str)
{
	int ret;
	int	i;

	ret = -1;
	while (g_env[++ret])
	{
		i = 0;
		while (str[i] && g_env[ret][i] && str[i] == g_env[ret][i])
		{
			if (str[i] == '=')
				return (ret);
			++i;
		}
		if (!str[i] && g_env[ret][i] == '=')
			return (ret);
	}
	return (-1);
}

int	 ft_atoi(const char *str)
{
		int	 i;
		int	 minus;
		int	 rez;

		rez = 0;
		i = 0;
		minus = 1;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
				++i;
		if (str[i] == '+' || str[i] == '-')
		{
				if (str[i] == '-')
						minus = -1;
				++i;
		}
		while (str[i] >= 48 && str[i] <= 57)
		{
				rez = rez * 10 + (str[i] - 48);
				++i;
		}
		return (rez * minus);
}
