/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 02:54:09 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 03:09:41 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_unset(t_cmd *cmd)
{
	int	alrd_here;

	alrd_here = get_var_name_end(cmd->cm_argv[1]);
	if (alrd_here != -1)
	{
		while(g_env[alrd_here])
		{
			g_env[alrd_here] = g_env[alrd_here + 1];
			++alrd_here;
		}		
	}
	return (0);
}