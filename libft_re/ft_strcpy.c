/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 12:09:09 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/25 15:17:19 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	*ft_strcpy(char *dest, const char *src)
{
	unsigned char	*d;
	unsigned char	*s;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	while (*s)
		*(d++) = *(s++);
	return (dest);
}
