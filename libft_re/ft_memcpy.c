/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 08:33:40 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/30 08:33:51 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*buff;
	unsigned char	*tmp;

	tmp = (unsigned char*)src;
	buff = (unsigned char*)dst;
	if (!tmp && !buff)
		return (0);
	while (n--)
	{
		*buff = *tmp;
		buff++;
		tmp++;
	}
	return (dst);
}
