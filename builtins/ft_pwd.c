/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 13:15:30 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/27 16:08:15 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_pwd(t_mini *mini)
{
	char	*dir;
	char	*buf;

	buf = NULL;
	dir = getcwd(buf, 0);
	if (dir)
	{
		write(1, dir, ft_strlen(dir));
		write(1, "\n", 1);
		return (0);
	}
	return (set_error(mini, N_PWD, 1, NULL));
}
