/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mv_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/19 06:25:26 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/03 22:11:51 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	mv_str_left(char *str)
{
	int	i;

	i = -1;
	while (str[++i + 1])
		str[i] = str[i + 1];
	str[i] = '\0';
}
