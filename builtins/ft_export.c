/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 01:46:28 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 03:04:36 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

char	**realloc_genv(t_cmd *cmd)
{
	int		i;
	char	**newg_env;

	i = 0;
	while (g_env[i])
		++i;
	newg_env = malloc ((i + 2) * sizeof(char*));
	if (!newg_env)
		return (NULL);
	i = -1;
	while (g_env[++i])
		newg_env[i] = g_env[i];
	newg_env[i] = ft_strdup(cmd->cm_argv[1]);
	if (!newg_env[i])
	{
		free(newg_env);
		return (NULL);
	}
	newg_env[i + 1] = NULL;
	return (newg_env);
}

int	ft_export(t_cmd *cmd)
{
	char	**newg_env;
	int		alrd_here;

	alrd_here = get_var_name_end(cmd->cm_argv[1]);
	if (alrd_here != -1)
	{
		free(g_env[alrd_here]);
		g_env[alrd_here] = ft_strdup(cmd->cm_argv[1]);
		return (0);
	}
	newg_env = realloc_genv(cmd);
	if (!newg_env)
		return (1);
	free(g_env);
	g_env = newg_env;
	return (0);
}