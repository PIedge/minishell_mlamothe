/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 09:28:05 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/05 09:28:35 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_re.h"

void	*ft_realloc(void *ptr, size_t size)
{
	char	*ret;
	size_t	len;

	ret = 0;
	if (!ptr)
		return (malloc(sizeof(char) * size));
	if (!size)
	{
		free(ptr);
		return (ret);
	}
	ret = malloc(sizeof(char) * size);
	if (!ret)
		return (0);
	len = ft_strlen(ptr);
	if (size > len)
		ft_memcpy(ret, ptr, len);
	if (size < len || size == len)
		ft_memcpy(ret, ptr, size);
	free(ptr);
	return (ret);
}
