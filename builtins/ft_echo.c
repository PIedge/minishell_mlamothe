/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:25:39 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 15:47:45 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_write_echo(t_cmd *tmp, int i)
{
	int		j;

	j = -1;
	while (tmp->cm_argv[i][++j])
	{
		write(STDOUT_FILENO, &tmp->cm_argv[i][j], 1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*tmp;
	int		i;
	int		opt;

	(void)mini;
	i = 0;
	opt = 0;
	tmp = cmd;
	while (tmp->cm_argv[++i] && !ft_strcmp(tmp->cm_argv[i], "-n"))
		opt = 1;
	--i;
	while (tmp->cm_argv[++i])
	{
		if (ft_write_echo(tmp, i))
			return (1);
		if (tmp->cm_argv[i + 1])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!opt)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
