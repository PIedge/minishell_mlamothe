/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 04:23:07 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/31 06:26:51 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"
#include <stdlib.h>

/*int	get_var_name_end(char *var)
{
	int	i;

	i = 0;
	while (*var != '=')
	{
		++var;
		++i;
	}
	return (i);
}*/

char	*find_var(char **env, char *var_name)
{
	int	y;

	y = -1;
	if (!env)
		return (NULL);
	while (env[++y])
	{
		if (!(ft_strncmp(env[y], var_name, ft_strlen(var_name))))
			return (env[y]);
	}
	return (NULL);
}

char	*find_var_with_limit(char **env, char *start, char *end)
{
	int	y;

	y = -1;
	if (*start == '?')
		return (ft_itoa(g_lrest));
	while (env[++y])
		if (!(ft_strncmp(env[y], start, end - start)))
			return (env[y]);
	return (0);
}

char	**copy_env(char **env)
{
	char	**new;
	int	y;

	y = 0;
	while (env[y])
		++y;
	new = malloc(sizeof(char *) * (y + 1));
	if (!new)
		return (0);
	while (y >= 0)
		new[y--] = 0;
	while (env[++y])
	{
		new[y] = ft_substr((const char *)env[y], 0, ft_strlen(env[y]));
		if (!(new[y]))
		{
			ft_double_tab_free(new);
			return (0);
		}
	}
	return (new);
}