#include <stdio.h>	
#include "includes/minishell.h"
#include "libft_re/libft_re.h"

int	main(int ac, char **av)
{
	ac = 0;
	av = 0;
	char *rl;

	while (1)
	{
		rl = ft_readline("UwU");
		if (!rl)
			return (printf("Error\n"));
		printf("|%s|\n", rl);
	}
	
}