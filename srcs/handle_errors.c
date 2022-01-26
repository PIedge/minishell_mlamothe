/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:26:14 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 16:36:55 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	set_error(t_mini *mini, int err, int ret)
{
	mini->err = err;
	return (ret);
}

void	wr_err(char *err)
{
	write(2, err, strlen(err));
}

void	select_err(int err)
{
	if (err >= 1 && err <= 8)
	{
		perror(NULL);
		return ;
	}
	if (err == 0)
		return (wr_err(E_MALLOC));
	if (err == 20)
		return (wr_err(E_CDMARGS));
	if (err == 21)
		return (wr_err(E_CDFARGS));
	if (err == 22)
		return (wr_err(E_CDCHDIR));
	if (err == 23)
		return (wr_err(E_PWD));
}
