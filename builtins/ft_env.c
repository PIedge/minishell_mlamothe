/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 02:57:51 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/30 19:36:49 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_env(t_cmd *cmd, t_mini *mini)
{
	int	i;

	(void)cmd;
	(void)mini;
	if (mini->env)
	{
		i = -1;
		while (mini->env[++i])
			printf("%s\n", mini->env[i]);
		return (0);
	}
	return (1);
}
