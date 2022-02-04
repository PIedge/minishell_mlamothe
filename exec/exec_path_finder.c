/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_finder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:19:46 by mlamothe          #+#    #+#             */
/*   Updated: 2022/02/04 11:54:17 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

char	**get_split(t_cmd *cmd, t_mini *mini)
{
	char	*var;
	char	**splt;

	var = find_var(mini->env, "PATH");
	if (!var)
	{
		set_error(mini, N_ACCESS, 1, cmd->cm_argv[0]);
		return (NULL);
	}
	var += 5;
	splt = ft_split(var, ':');
	return (splt);
}

int	check_path_cmd(t_cmd *cmd, t_mini *mini)
{
	char	**splt;
	char	*join;
	int		i;

	if (!access(cmd->cm_argv[0], X_OK))
		return (0);
	splt = get_split(cmd, mini);
	if (!splt)
		return (1);
	i = -1;
	while (splt[++i])
	{
		join = ft_join_cmd(splt[i], cmd->cm_argv[0], mini);
		if (!join)
			return (ft_free_split(splt, 1));
		if (!access(join, R_OK))
		{
			free(cmd->cm_argv[0]);
			cmd->cm_argv[0] = join;
			return (ft_free_split(splt, 0));
		}
		free(join);
	}
	ft_free_split(splt, 0);
	return (set_error(mini, N_ACCESS, 1, cmd->cm_argv[0]));
}

int	check_path_out(t_cmd *cmd, t_mini *mini)
{
	int		fd;
	t_redir	*tmp;

	tmp = cmd->out;
	while (tmp)
	{
		if (access(tmp->word, W_OK))
		{
			if (errno != ENOENT)
				return (set_error(mini, N_ACCESS, 1, tmp->word));
			else
			{
				fd = open(tmp->word, O_WRONLY | O_CREAT, 0666);
				if (fd == -1)
					return (set_error(mini, N_OPEN, 1, tmp->word));
				close(fd);
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

int	check_path_redir(t_cmd *cmd, t_mini *mini)
{
	t_redir	*tmp;

	tmp = cmd->in;
	while (tmp)
	{
		if (tmp->type)
		{
			if (handle_hd(mini, tmp))
				return (1);
		}
		else if (access(cmd->in->word, R_OK))
			return (set_error(mini, N_ACCESS, 1, cmd->in->word));
		tmp = tmp->next;
	}
	return (check_path_out(cmd, mini));
}

int	check_paths_ok(t_cmd *cmd, t_mini *mini)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->cm_argv || !tmp->cm_argv[0])
			return (set_error(mini, N_SYNTAX, 1, NULL));
		if (check_path_redir(tmp, mini))
			return (1);
		tmp = tmp->next;
	}
	tmp = cmd;
	while (tmp)
	{
		if (tmp->cm_argv[0] && !is_builtin(tmp->cm_argv[0]))
			if (check_path_cmd(tmp, mini))
				return (1);
		tmp = tmp->next;
	}
	return (0);
}
