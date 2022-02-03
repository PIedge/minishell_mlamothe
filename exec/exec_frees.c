/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_frees.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:25:51 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/03 10:26:55 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

void	ft_free_exit(t_mini *mini, int ret)
{
	free(mini->cmd_ori);
	free_cmd(mini->cmd);
	ft_double_tab_free(mini->env);
	rl_clear_history();
	exit(ret);
}

void	ft_free_exit_hd(t_mini *mini, int ret)
{
	free(mini->cmd_ori);
	free_cmd(mini->cmd);
	ft_double_tab_free(mini->env);
	rl_clear_history();
	exit(ret);
}

int	ft_free_split(char	**splt, int ret)
{
	int	i;

	i = -1;
	while (splt[++i])
		free(splt[i]);
	free(splt);
	return (ret);
}
