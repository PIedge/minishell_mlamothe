/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:25:39 by mlamothe          #+#    #+#             */
/*   Updated: 2021/12/22 16:05:24 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_write_var(int *j, char *str, t_map env)
{
	int		i;
	int		jtmp;
	char	*var;
	char	*ret_var;

	i = 0;
	jtmp = *j;
	while (str[++jtmp] && str[jtmp] != ' ')
		++i;
	var = malloc(sizeof(char) * (i + 1));
	if (!var)
		return (1);
	i = -1;
	while (str[++(*j)] && str[*j] != ' ')
		var[++i] = str[*j];
	var[++i] = 0;
	ret_var = ft_get_var(var, env);
	free (var);
	--(*j);
	if (ret_var)
		write(STDOUT_FILENO, ret_var, ft_strlen(ret_var));
	return (0);
}

int	ft_write_echo(t_cmd *tmp, t_map env, int i)
{
	int		j;
	
	j = 0;
	while (tmp->cm_argv[++i][++j] && j < ft_strlen(tmp->cm_argv[++i][++j]) - 1)
	{
		if (tmp->cm_argv[i][j] == '$' && tmp->cm_argv[i][0] == '\"')
			if (ft_write_var(&j, tmp->cm_argv[i], env))
				return (1);
		else
			write(STDOUT_FILENO, tmp->cm_argv[i][++j], 1);
	}
	return (0);
}

int	ft_echo(t_cmd *cmd, t_map env)
{
	t_cmd	*tmp;
	int		i;
	int		opt;

	i = 0;
	opt = 0;
	tmp = cmd;
	while (tmp->cm_argv[++i])
	{
		if (!ft_strcmp(tmp->cm_argv[i], "-n"))
			opt = 1;
		else
			--i;
	}
	--i;
	if (ft_write_echo(tmp, env, i))
		return (1);
	if (!opt)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
