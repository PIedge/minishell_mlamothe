/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_finder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:19:46 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/24 19:04:29 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

int	ft_free_split(char	**splt, int ret)
{
	int	i;

	i = -1;
	while (splt[++i])
		free(splt[i]);
	free(splt);
	return (ret);
}

int	check_path_cmd(t_cmd *cmd)
{
	char	**splt;
	char	*join;
	int		i;

	splt = ft_split(find_var(g_env, "PATH") + 5, ':');
	if (!splt)
		return (1);
	i = -1;
	while (splt[++i])
	{
		join = ft_join_cmd(splt[i], cmd->cm_argv[0]);
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

int	check_path_redir(t_cmd *cmd)	//MODIF DES IN ET OUTS REQUIS
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
	{
		if (access(tmp->word, W_OK))
		{
			if (errno != ENOENT)
				return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_paths_ok(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while(tmp)
	{
		if (tmp->cm_argv[0] && !is_builtin(tmp->cm_argv[0]))
			if (check_path_cmd(tmp))
				return (1);
		tmp = tmp->next;
	}
	printf("    check_path_cmd\t\e[1;32mV\e[0m\n");
	tmp = cmd;
	if (check_path_redir(tmp))
			return (1);
	printf("    check_path_redir\t\e[1;32mV\e[0m\n");
	return (0);
}
