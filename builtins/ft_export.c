/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 01:46:28 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 15:56:25 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

char	**realloc_env(t_cmd *cmd, t_mini *mini)
{
	int		i;
	char	**new_env;

	i = 0;
	while (mini->env[i])
		++i;
	new_env = malloc ((i + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	i = -1;
	while (mini->env[++i])
		new_env[i] = mini->env[i];
	new_env[i] = ft_strdup(cmd->cm_argv[1], mini);
	new_env[i + 1] = NULL;
	if (!new_env[i])
	{
		free(new_env);
		return (NULL);
	}
	return (new_env);
}

int	ft_env_export(t_mini *mini)
{
	int	i;

	if (mini->env)
	{
		i = -1;
		while (mini->env[++i])
			printf("declare -x %s\n", mini->env[i]);
		return (0);
	}
	return (1);
}

int	check_name_var_val(char *name)
{
	int	i;

	i = 0;
	if ((name[i] < 'a' || name[i] > 'z') && \
		(name[i] < 'A' || name [i] > 'Z') && name[i] != '_')
		return (0);
	++i;
	while (name[i])
	{
		if ((name[i] < 'a' || name[i] > 'z') && \
			(name[i] < 'A' || name [i] > 'Z') && \
				name[i] != '_' && (name[i] < '0' || name[i] > '9'))
			return (i);
		++i;
	}
	return (1);
}

int	ft_export(t_cmd *cmd, t_mini *mini)
{
	char	**new_env;
	int		alrd_here;
	int		cc;

	if (!cmd->cm_argv[1])
		return (ft_env_export(mini));
	cc = check_name_var_val(cmd->cm_argv[1]);
	if (cc == 0 || cmd->cm_argv[1][cc] != '=')
		return (set_error(mini, 1, 1, NULL));
	alrd_here = get_var_name_end(cmd->cm_argv[1], mini);
	if (alrd_here != -1)
	{
		free(mini->env[alrd_here]);
		mini->env[alrd_here] = ft_strdup(cmd->cm_argv[1], mini);
		return (0);
	}
	new_env = realloc_env(cmd, mini);
	if (!new_env)
		return (1);
	free(mini->env);
	mini->env = new_env;
	return (0);
}
