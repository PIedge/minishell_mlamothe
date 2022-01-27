/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 02:57:51 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/27 13:17:51 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_env(t_cmd *cmd, t_mini *mini)
{
	int	i;

	(void)cmd;
	(void)mini;
	i = -1;
	while (mini->env[++i])
		printf("%s\n", mini->env[i]);
	return (0);
}
