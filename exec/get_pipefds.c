/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipefds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:13:49 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 13:04:53 by mlamothe         ###   ########.fr       */
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
	pipefds = malloc((i + 1) * sizeof(int *));
	if (!pipefds)
		if (!set_error(mini, N_MALLOC, 0, NULL))
			return (NULL);
	j = -1;
	while (++j < i)
	{
		pipefds[j] = malloc (2 * sizeof(int));
		if (!pipefds[j])
		{
			ft_free_pipefds(pipefds, j, 1, mini);
			return (NULL);
		}
	}
	pipefds[j] = NULL;
	return (pipefds);
}

int	ft_free_pipefds(int **pipefds, int n, int ret, t_mini *mini)
{
	int	i;

	i = -1;
	if (ret == 2)
		set_error(mini, N_MALLOC, 0, NULL);
	if (pipefds)
	{
		while (pipefds[++i] && i <= n)
			free(pipefds[i]);
		free(pipefds);
	}
	if (ret == 2)
		return (1);
	return (ret);
}
