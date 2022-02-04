/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_waits.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 10:13:16 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 08:25:54 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

void	waitchild(int nb_cmds, t_mini *mini)
{
	int	status;

	while (--nb_cmds >= 0)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			mini->err = status >> 8;
			if (WTERMSIG(status) || g_lrest == 130)
			{
				g_lrest = 130;
				ft_free_exit(mini, mini->err);
			}
		}
		else
		{
			g_lrest = status >> 8;
			mini->err = status >> 8;
		}
	}
}

int	waitparent(int nb_cmds, t_mini *mini)
{
	int	status;

	while (--nb_cmds >= 0)
	{
		waitpid(-1, &status, WUNTRACED);
		if (WIFSIGNALED(status))
		{
			g_lrest = status >> 8;
			mini->err = status >> 8;
			if (WTERMSIG(status))
			{
				g_lrest = 130;
				return (1);
			}
		}
		else
		{
			WEXITSTATUS(status);
			mini->err = status >> 8;
			if (status)
				g_lrest = 1;
		}
	}
	return (0);
}
