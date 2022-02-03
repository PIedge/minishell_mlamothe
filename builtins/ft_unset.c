/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 02:54:09 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/03 14:29:18 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_unset(t_cmd *cmd, t_mini *mini)
{
	int	alrd_here;

	if (!cmd->cm_argv[1])
		return (0);
	alrd_here = get_var_name_end(cmd->cm_argv[1], mini);
	if (alrd_here != -1)
	{
		free(mini->env[alrd_here]);
		while (mini->env[alrd_here])
		{
			mini->env[alrd_here] = mini->env[alrd_here + 1];
			++alrd_here;
		}
	}
	return (0);
}
