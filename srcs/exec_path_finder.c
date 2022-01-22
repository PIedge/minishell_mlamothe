/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_finder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:19:46 by mlamothe          #+#    #+#             */
/*   Updated: 2021/12/22 13:54:32 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_free_split(char	**splt, int ret)
{
	int	i;

	i = -1;
	while (splt[++i])
		free(splt[i]);
	free(splt);
	return (ret);
}

int	check_path_cmd(t_cmd *cmd, t_map env)
{
	char	**splt;
	char	*join;
	int		i;

	splt = ft_split(ft_get_var("PATH", env), ':');
	if (!splt)
		return (1);
	i = -1;
	while (splt[++i])
	{
		join = ft_join(splt[i], cmd->cmd);
		if (!join)
			return (ft_free_split(splt, 1));
		if (!access(join, R_OK))
		{
			free(cmd->cmd);
			cmd->cmd = join;
			return (ft_free_split(splt, 0));
		}
		free(join);
	}
	free(splt);
	return (1);
}

int	check_path_redir(t_cmd *cmd, t_map env)	//MODIF DES IN ET OUTS REQUIS
{
	t_redir	*tmp;

	tmp = cmd->in;
	while (tmp)
	{
		if (!tmp->type)
			if (access(cmd->in->word, R_OK))
				return (1);
		tmp = tmp->next;
	}
	tmp = cmd->out;
	while (tmp)
		if (access(tmp->word, W_OK))
			if (errno != ENOENT)
				return (1);
	return (0);
}

int	check_paths_ok(t_cmd *cmd, t_map env)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!is_builtin(tmp->cmd))
			if (check_path_cmd(tmp, env))
				return (1);
		if (check_path_redir(tmp, env))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
