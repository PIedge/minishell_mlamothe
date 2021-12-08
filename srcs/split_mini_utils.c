/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 19:06:39 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/08 19:50:18 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	skip_quotes(char *str, int *i, char c)
{
	++(*i);
	while (str[*i] && str[*i] != c)
		++(*i);
	if (str[*i] == c)
		++(*i);
}