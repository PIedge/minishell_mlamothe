/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 12:42:24 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/24 13:03:15 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_cd(t_cmd *cmd)
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
			closedir(dir);
		if (chdir(cmd->cm_argv[1]))
			return (1);
	}
	else
		return (1);
	return (0);
}