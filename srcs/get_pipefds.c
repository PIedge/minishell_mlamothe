/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipefds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:13:49 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 13:54:44 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	**get_pfd(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*tmp;
	int		**pipefds;
	int		i;
	int		j;

	i = 0;
	tmp = cmd;
	while (tmp->next && ++i)
		tmp = tmp->next;
	pipefds = malloc(i * sizeof(int *));
	if (!pipefds)
		if (!set_error(mini, 0, 0))
			return (NULL);
	j = -1;
	while (++j < i)
	{
		pipefds[j] = malloc (2 * sizeof(int));
		if (!pipefds[j])
		{
			ft_free_pipefds(pipefds, 0);
			set_error(mini, 0, 0);
			return (NULL);
		}
	}
	return (pipefds);
}

int	ft_free_pipefds(int **pipefds, int ret)
{
	int	i;

	i = -1;
	while (pipefds[++i])
		free(pipefds[i]);
	free(pipefds);
	return (ret);
}
