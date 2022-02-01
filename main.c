/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 08:48:17 by tmerrien          #+#    #+#             */
/*   Updated: 2022/02/01 22:44:56 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "libft_re/libft_re.h"

int	g_lrest;

int	init_mini(t_mini *mini, char **envp)
{
	int		i;
	int		n;
	char	*nbr;

	init_signals(mini);
	mini->err = 0;
	g_lrest = 0;
	mini->err_word = NULL;
	mini->cmd = NULL;
	mini->env = copy_env(envp);
	if (!(mini->env))
		return (0);
	i = get_var_name_end("SHLVL", mini);
	if (i != -1)
	{
		n = ft_atoi(mini->env[i] + 6);
		free(mini->env[i]);
		nbr = ft_itoa(n + 1);
		if (!nbr)
			return (0);
		mini->env[i] = ft_join("SHLVL=", nbr, mini);
		free(nbr);
		if (!mini->env[i])
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
		ret = minishell(&mini);
		free(mini.cmd_ori);
		mini.cmd_ori = NULL;
		free_cmd(mini.cmd);
		mini.cmd = NULL;
	//	if(mini.err)
	//		printf("\e[1;31merr code : %d\e[0m\n", mini.err);
	}
	free(mini.cmd_ori);
	free_cmd(mini.cmd);
	ft_double_tab_free(mini.env);
	printf("minishell done\n");
	/*
	** TEST ZONE END
	*/
	return (0);
}