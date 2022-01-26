/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 18:42:42 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 16:18:49 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_re.h"
#include <stdio.h>

char	*set_word(int n, int i)
{
	char	*word;

	if (n < 0)
	{
		word = malloc((i + 2) * sizeof(char));
		if (!(word))
			return (NULL);
		word[0] = '-';
	}
	else
	{
		word = malloc((i + 1) * sizeof(char));
		if (!(word))
			return (NULL);
	}
	return (word);
}

void	*ft_itoa2(int n, long *nbr, int *i, int *j)
{
	char	*word;

	*i = 0;
	*nbr = n;
	*nbr = *nbr / 10;
	while (*nbr)
	{
		++(*i);
		*nbr = *nbr / 10;
	}
	++(*i);
	word = set_word(n, *i);
	if (!word)
		return (NULL);
	if (n < 0)
		*j = 0;
	else
		*j = -1;
	if (n < 0)
		++i;
	return (word);
}

char	*ft_itoa(int n)
{
	long	nbr;
	int		i;
	int		j;
	char	*word;

	word = ft_itoa2(n, &nbr, &i, &j);
	if (!word)
		return (NULL);
	word[i] = 0;
	nbr = n;
	if (n < 0)
		nbr = nbr * -1;
	while (j < --i)
	{
		word[i] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (word);
}
