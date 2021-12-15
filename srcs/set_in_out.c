/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_in_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:07:52 by mlamothe          #+#    #+#             */
/*   Updated: 2021/12/13 16:12:52 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	set_out(int *out, t_redir *redir)
{
	t_redir	*ret;
	t_redir	*tmp;

	*out = -1;
	ret = NULL;
	tmp = redir;
	while (tmp)
	{
		if (!(tmp->type & IN))
			ret = tmp;
		tmp = tmp->next;
	}
	if (!ret)
		return (0);
	if (ret->type & TWO)
		*out = open(tmp->word, O_WRONLY | O_CREAT | O_APPEND, 0666);
	else
		*out = open(tmp->word, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (*out == -1)
		return (1);
	return (0);
}

int	set_in(int *in, t_redir *redir)
{
	t_redir	*ret;
	t_redir	*tmp;

	*in = -1;
	ret = NULL;
	tmp = redir;
	while (tmp)
	{
		if (tmp->type & IN)
			if (!(tmp->type & TWO))
				ret = tmp;
		tmp = tmp->next;
	}
	if (!ret)
		return (0);
	*in = open(ret->word, O_RDONLY);
	if (*in == -1)
		return (1);
	return (0);
}

int	ft_closeem(int in, int out, int ret)
{
	if (in != -1)
		close (in);
	if (out != -1)
		close (out);
	return (ret);
}

int	set_in_n_out(int *in, int *out, t_redir *redir)
{
	if (set_in(in, redir))
		return (1);
	if (*in != -1)
		if (dup2(*in, 0))
			return (ft_closeem(*in, *out, 1));
	if (set_out(out, redir))
		return (ft_closeem(*in, *out, 1));
	if (*out != -1)
		if (dup2(*out, 0))
			return (ft_closeem(*in, *out, 1));
	return (ft_closeem(*in, *out, 0));
}
