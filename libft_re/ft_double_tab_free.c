/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_double_tab_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:42:19 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/30 09:49:41 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_double_tab_free(char **tab)
{
	int	i;

	i = -1;
	while (tab && tab[++i])
		free(tab[i]);
	free(tab);
}
