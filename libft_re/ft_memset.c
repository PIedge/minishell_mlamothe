/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 08:42:51 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 14:48:04 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_memset(void *b, int n)
{
	char	*t;

	t = (char *)b;
	while (--n >= 0)
	{
		*t = 0;
	}
}
