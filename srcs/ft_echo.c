/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:25:39 by mlamothe          #+#    #+#             */
/*   Updated: 2021/12/13 18:05:24 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_write_var(char *str)
{

}

int	ft_echo(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		i;
	int		j;
	int		opt;

	i = 0;
	opt = 0;
	tmp = cmd;
	while (tmp->cm_argv[++i])
	{
		if (!ft_strcmp(tmp->cm_argv[i], "-n"))
			opt = 1;
		j = -1;
		while (tmp->cm_argv[i][++j])
		{
			if (tmp->cm_argv[i][++j])
			write();
		}
	}
	if (!opt)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}

// THEO : VARIABLES et PATH et quoi dans cm_argv ('' ou "" ou rien)