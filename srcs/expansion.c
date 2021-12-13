/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:45:59 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/12 21:18:58 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft_re/libft_re.h"

void	calc_vars_len(char *s, int *i, int *len_add, int *len_var_name)
{

}

int	is_variable(char *s)
{
	int	i;

	i = -1;
	while (ft_is_white_space(s[++i]))
	{
		if (i == 0)
			if (!ft_isalpha(s[i]) && s[i] != '_')
				return (0);
		else if (i > 0)
			if (!ft_isalpha(s[i]) && !ft_isdigit(s[i]))
				return (0);
	}
	return (1);
}

int	how_much_space_needed(char *s)
{
	int	ini_len;
	int	len_add;
	int	len_var_name;
	int	i;

	ini_len = (int)ft_strlen(s);
	i = 0;
	len_add = 0;
	len_var_name = 0;
	while (++i)
	{
		if (is_variable(&(s[i])))
			calc_vars_len(s, &i, &len_add, &len_var_name);
	}
}