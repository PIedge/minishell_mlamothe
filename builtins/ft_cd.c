/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:42:24 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/03 11:12:48 by mlamothe         ###   ########.fr       */
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
		dir = opendir(cmd->cm_argv[1]);
		if (!dir)
			return (set_error(mini, N_OPENDIR, 1, NULL));
		else
			closedir(dir);
		if (chdir(cmd->cm_argv[1]))
			return (set_error(mini, N_CDCHDIR, 1, NULL));
	}
	else
		return (set_error(mini, N_CDFARGS, 1, NULL));
	return (0);
}
