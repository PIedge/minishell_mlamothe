/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 14:26:14 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/03 16:32:18 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	set_error(t_mini *mini, int err, int ret, char *str)
{
	mini->err = err;
	g_lrest = err;
	mini->err_word = str;
	return (ret);
}

void	wr_err(char *err, char *str)
{
	write(2, err, strlen(err));
	if (str)
	{
		write(2, str, strlen(str));
		write(2, "\n", 1);
	}
}

void	wr_perror(int err, char *str)
{
	if (str)
		return (perror(str));
	if (err == 2)
		return (perror("execve"));
	if (err == 3)
		return (perror("pipe"));
	if (err == 4)
		return (perror("dup2"));
	if (err == 5)
		return (perror("fork"));
	if (err == 6)
		return (perror("opendir"));
	if (err == 7)
		return (perror("open"));
	if (err == 8)
		return (perror("unlink"));
	if (err == 9)
		return (perror("access"));
}

void	select_err(int err, char *str)
{
	if (err > N_MALLOC && err <= N_EXECVE)
		return (wr_perror(err, str));
	if (err == 1)
		return ;
	if (err == N_MALLOC)
		return (wr_err(E_MALLOC, NULL));
	if (err == 20)
		return (wr_err(E_CDMARGS, NULL));
	if (err == 21)
		return (wr_err(E_CDFARGS, NULL));
	if (err == 22)
		return (wr_err(E_CDCHDIR, NULL));
	if (err == 23)
		return (wr_err(E_PWD, NULL));
	if (err == 24)
		return (wr_err(E_VAR, str));
}
