/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double_tab.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:39:05 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/28 18:39:15 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	ft_printf_double_tab(char **av, char *name)
{
	int	i;

	if (!av)
		printf("No tab detected, make sure %s is allocated.\n", name);
	i = 0;
	while (av[i])
	{
		printf("%s\n", av[i]);
		++i;
	}
}