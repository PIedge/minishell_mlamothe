/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:42:24 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/05 15:53:10 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

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
		set_oldpwd(mini);
		if (chdir(cmd->cm_argv[1]))
			return (set_error(mini, N_CDCHDIR, 1, NULL));
	}
	else
		return (open_home(mini));
	ft_setnewpwd(mini);
	return (0);
}
