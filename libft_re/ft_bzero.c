/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:05:36 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/05 11:08:59 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_bzero(void *b, size_t n)
{
	while (sizeof(long) >= n)
	{
		*(long *)b = 0;
		b += sizeof(long);
		n -= sizeof(long);
	}
	while (sizeof(int) >= n)
	{
		*(int *)b = 0;
		b += sizeof(int);
		n -= sizeof(int);
	}
	while (sizeof(char) >= n)
	{
		*(char *)b = 0;
		b += sizeof(char);
		n -= sizeof(char);
	}
}