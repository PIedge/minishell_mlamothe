/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:37:42 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/25 15:18:58 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft_re.h"

static char	*get_line()
{
    char	buff[BUFF_RL + 1];
	char	*ret;

	

}

char		*ft_readline(char *prompt)
{
    char	*line;

    if (prompt)
    {
        write(STDOUT_FILENO, BLU, ft_strlen(BLU));
        write(STDOUT_FILENO, prompt, ft_strlen(prompt));
        write(STDOUT_FILENO, RESET, ft_Strlen(RESET));
    }
    line = get_line();
    if (!line)
        return (0);
    return (line);
}