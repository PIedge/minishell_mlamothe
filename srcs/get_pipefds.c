/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipefds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:13:49 by mlamothe          #+#    #+#             */
/*   Updated: 2021/12/13 16:16:01 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	**get_pfd(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		**pipefds;
	int		i;
	int		j;

	tmp = cmd;
	while (tmp->next && ++i)
		tmp = tmp->next;
	pipefds = malloc((i + 1) * sizeof(int *));
	if (!pipefds)
		return (NULL);
	pipefds[i] = NULL;
	j = -1;
	while (++j < i)
	{
		pipefds[j] = malloc (2 * sizeof(int));
		if (!pipefds[j])
		{
			ft_free_pipefds(pipefds, 0);
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
