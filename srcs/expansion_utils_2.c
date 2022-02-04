/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:19:28 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/04 10:56:48 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_re/libft_re.h"
#include "../includes/minishell.h"
#include <stdlib.h>

int	get_end_index(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '?')
		return (1);
	++i;
	while (str[i] && !ft_is_white_space(str[i]) && str[i] != '$' && \
		str[i] != '"')
		++i;
	return (i);
}
