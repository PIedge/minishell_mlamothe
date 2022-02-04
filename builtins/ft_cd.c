/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:42:24 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 15:51:55 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	open_home(t_mini *mini)
{
	DIR		*dir;
	int		i;
	char	*home;

	i = get_var_name_end("HOME", mini);
	if (i >= 0)
	{
		home = mini->env[i] + 5;
		dir = opendir(home);
		if (!dir)
			return (set_error(mini, N_OPENDIR, 1, "~"));
		closedir(dir);
		if (chdir(home))
			return (set_error(mini, N_CDCHDIR, 1, NULL));
		return (0);
	}
	return (set_error(mini, 1, 1, NULL));
}

char	**realloc_env_cd(char *str, t_mini *mini)
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
	new_env[i] = str;
	new_env[i + 1] = NULL;
	return (new_env);
}

int	set_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	char	*tmp;
	int		i;
	char	**new_env;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	oldpwd = ft_join("OLDPWD=", tmp, mini);
	free(tmp);
	if (!oldpwd)
		return (1);
	i = get_var_name_end("OLDPWD", mini);
	if (i == -1)
	{
		new_env = realloc_env_cd(oldpwd, mini);
		if (!new_env)
			return (1);
		free(mini->env);
		mini->env = new_env;
		return (0);
	}
	free(mini->env[i]);
	mini->env[i] = oldpwd;
	return (0);
}

int	ft_setnewpwd(t_mini *mini)
{
	char	*newpwd;
	char	*tmp;
	int		i;
	char	**new_env;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	newpwd = ft_join("PWD=", tmp, mini);
	free(tmp);
	if (!newpwd)
		return (1);
	i = get_var_name_end("PWD", mini);
	if (i == -1)
	{
		new_env = realloc_env_cd(newpwd, mini);
		if (!new_env)
			return (1);
		free(mini->env);
		mini->env = new_env;
		return (0);
	}
	free(mini->env[i]);
	mini->env[i] = newpwd;
	return (0);
}

int	ft_cd(t_cmd *cmd, t_mini *mini)
{
	DIR		*dir;

	if (cmd->cm_argv[1])
	{
		if (cmd->cm_argv[2])
			return (set_error(mini, N_CDMARGS, 1, NULL));
		if (!ft_strcmp(cmd->cm_argv[1], "~"))
			return (open_home(mini));
		else
			dir = opendir(cmd->cm_argv[1]);
		if (!dir)
			return (set_error(mini, N_OPENDIR, 1, cmd->cm_argv[1]));
		closedir(dir);
		if (set_oldpwd(mini))
			return (1);
		if (chdir(cmd->cm_argv[1]))
			return (set_error(mini, N_CDCHDIR, 1, NULL));
	}
	else
		return (open_home(mini));
	if (ft_setnewpwd(mini))
		return (1);
	return (0);
}
