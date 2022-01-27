/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 00:32:02 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/27 00:50:08 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_re.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	test;
	size_t	i;

	i = 0;
	if (!(sub = malloc(sizeof(char) * (len + 1))))
		return (0);
	sub[i] = 0;
	if (!s)
		return (0);
	test = ft_strlen((char *)s);
	if (test < start)
		return (sub);
	while (i < len && s[i + start])
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
