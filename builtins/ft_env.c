/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 02:57:51 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 03:03:05 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_env(t_cmd *cmd)
{
	int	i;

	(void)cmd;
	i = -1;
	while(g_env[++i])
		printf("%s\n", g_env[i]);
	return (0);
}