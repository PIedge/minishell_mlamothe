/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 12:31:13 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 16:46:42 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	is_numeric(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (0);
	return (1);
}

void	ft_exit(t_cmd *cmd, t_mini *mini)
{
	int	nb;

	if (!cmd->cm_argv[1])
		ft_free_exit(mini, 0);
	else if (cmd->cm_argv[2])
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		g_lrest = 1;
		return ;
	}
	if (!is_numeric(cmd->cm_argv[1]))
	{
		write(2, "minishell: exit: ", 17);
		write(2, cmd->cm_argv[1], ft_strlen(cmd->cm_argv[1]));
		write(2, ": numeric argument required\n", 28);
		ft_free_exit(mini, 2);
	}
	nb = ft_atoi(cmd->cm_argv[1]);
	if (nb < 0 || nb > 255)
		g_lrest = 1;
	else
		g_lrest = nb;
	ft_free_exit(mini, g_lrest);
}
