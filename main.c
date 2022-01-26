/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 08:48:17 by tmerrien          #+#    #+#             */
/*   Updated: 2022/01/26 23:06:56 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft_re/libft_re.h"


int	init_mini(t_mini *mini, char **envp)
{
	int		i;
	int		n;
	char	*nbr;

	mini->err = -1;
	mini->err_word = NULL;
	mini->cmd = NULL;
	g_env = copy_env(envp);
	if (!(g_env))
		return (0);
	i = get_var_name_end("SHLVL");
	if (i != -1)
	{
		n = ft_atoi(g_env[i] + 6);
		free(g_env[i]);
		nbr = ft_itoa(n + 1);
		if (!nbr)
			return (0);
		g_env[i] = ft_join("SHLVL=", nbr, mini);
		free(nbr);
		if (!g_env[i])
			return(0);
	}
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_mini	mini;

	av = 0;
	if (!init_mini(&mini, envp))
		destroy(&mini, E_MALLOC);
	// if (ac > 1)
		// destroy(&mini);
	/*
	** This main isn't finished, basicaly serves for test cases rn, you know what that means
	** TEST ZONE START
	*/
	ac = 0; //compilation problem if unused
	int	ret = 1;
	while (ret)
	{
		mini.cmd_ori = NULL;
		ret = minishell(&mini);
		free(mini.cmd_ori);
		free_cmd(mini.cmd);
		mini.cmd = NULL;
	}
	//printf("minishell done\n");
	/*
	** TEST ZONE END
	*/
	return (1);
}