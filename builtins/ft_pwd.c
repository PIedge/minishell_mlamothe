/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:15:30 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/22 13:31:36 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_cmd *cmd, t_map env)
{
	char	*dir;
	char	*buf;

	dir = getcwd(buf, 0);
	if (dir)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
	}
	else
		return (0);
}