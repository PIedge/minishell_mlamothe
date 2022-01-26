/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 16:19:45 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/26 22:38:57 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../libft_re/libft_re.h"

char	*get_path_hd(t_mini *mini, int i)
{
	char	*path;
	char	*nbr;

	nbr = ft_itoa(i);
	if (!nbr)
	{
		set_error(mini, 0, 0, NULL);
		return (NULL);
	}
	path = ft_join("./tmp/minishell-here_doc", nbr, mini);
	free(nbr);
	if (!path)
		return (NULL);
	return (path);
}

int	exec_init(t_mini *mini, t_cmd *cmd, int *dup_in, int *dup_out)
{
	t_cmd	*tmp;

	*dup_in = dup(STDIN_FILENO);
	*dup_out = dup(STDOUT_FILENO);
	if (*dup_in == -1 || *dup_out == -1)
		return (set_error(mini, 3, 1, NULL));
	tmp = cmd;
	if (check_paths_ok(tmp, mini))
		return (1);
	return (0);
}

int	get_var_name_end(char *str)
{
	int	ret;
	int	i;

	ret = -1;
	while (g_env[++ret])
	{
		i = 0;
		while (str[i] && g_env[ret][i] && str[i] == g_env[ret][i])
		{
			if (str[i] == '=')
				return (ret);
			++i;
		}
		if (!str[i] && g_env[ret][i] == '=')
			return (ret);
	}
	return (-1);
}
