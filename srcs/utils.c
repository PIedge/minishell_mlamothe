/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 14:00:11 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/24 13:40:18 by mlamothe         ###   ########.fr       */
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

char    *ft_join_cmd(char *str1, char *str2)
{
        int             i;
        int             j;
        char    *str_ret;

		if (str1[ft_strlen(str1 - 1)] == '/')
			str_ret = malloc((ft_strlen(str1) + ft_strlen(str2) + 2) * sizeof(char));
		else
        	str_ret = malloc((ft_strlen(str1) + ft_strlen(str2) + 1) * sizeof(char));
        if (!str_ret)
                return (NULL);
        i = -1;
        while (++i < (int)ft_strlen(str1))
                str_ret[i] = str1[i];
        j = -1;
		if (str1[ft_strlen(str1 - 1)] == '/')
			str_ret[i++] = '/';
        while (++j < (int)ft_strlen(str2))
                str_ret[i + j] = str2[j];
        str_ret[i + j] = 0;
        return (str_ret);
}
