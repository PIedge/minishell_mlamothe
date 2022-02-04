/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:19:28 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 16:15:48 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_re/libft_re.h"
#include "../includes/minishell.h"
#include <stdlib.h>

int	get_end_index(char *str)
{
	int	i;

	i = 1;
	if (str[i] == '?')
		return (1);
	if ((str[i] < 'a' || str[i] > 'z') && \
		(str[i] < 'A' || str [i] > 'Z') && str[i] != '_')
		return (1);
	++i;
	while (str[i])
	{
		if ((str[i] < 'a' || str[i] > 'z') && \
			(str[i] < 'A' || str [i] > 'Z') && \
				str[i] != '_' && (str[i] < '0' || str[i] > '9'))
			return (i);
		++i;
	}
	/*++i;
	while (str[i] && !ft_is_white_space(str[i]) && str[i] != '$' && \
		str[i] != '"')
		++i;*/
	return (i);
}
