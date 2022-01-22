/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:42:24 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/22 13:38:58 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd, t_map env)
{
	DIR		*dir;

	if (cmd->cm_argv[1])
	{
		if (cmd->cm_argv[2])
			return (1);
		dir = opendir(cmd->cm_argv[1]);
		if (!dir)
			return (1);
		else
			close (dir);
		if (chdir(dir))
			return (1);
	}
	else
		return (1);
	return (0);
}