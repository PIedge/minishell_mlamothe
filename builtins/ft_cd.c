/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:42:24 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/03 16:26:55 by mlamothe         ###   ########.fr       */
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
			return (set_error(mini, N_OPENDIR, 1, NULL));
		closedir(dir);
		if (chdir(home))
			return (set_error(mini, N_CDCHDIR, 1, NULL));
		return (0);
	}
	return (set_error(mini, N_VAR, 1, "HOME"));
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
			return (set_error(mini, N_OPENDIR, 1, NULL));
		closedir(dir);
		if (chdir(cmd->cm_argv[1]))
			return (set_error(mini, N_CDCHDIR, 1, NULL));
	}
	else
		return (set_error(mini, N_CDFARGS, 1, NULL));
	return (0);
}
