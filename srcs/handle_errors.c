/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:26:14 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 17:11:16 by mlamothe         ###   ########.fr       */
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

void	wr_perror(int err)
{
	if (err == 1)
		return (perror("execve"));
	if (err == 2)
		return (perror("pipe"));
	if (err == 3)
		return (perror("dup2"));
	if (err == 4)
		return (perror("fork"));
	if (err == 5)
		return (perror("opendir"));
	if (err == 6)
		return (perror("open"));
	if (err == 7)
		return (perror("unlink"));
	if (err == 8)
		return (perror("access"));
}

void	select_err(int err)
{
	if (err >= 1 && err <= 8)
		return (wr_perror(err));
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
