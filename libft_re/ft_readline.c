/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:37:42 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/01 12:58:35 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include "libft_re.h"

static char	*strjoin_diff(char *s1, char *s2)
{
	size_t	len_1;
	size_t	len_2;
	char	*new;

	len_1 = 0;
	if (s1)
		len_1 = ft_strlen(s1);
	len_2 = 0;
	if (s2)
		len_2 = ft_strlen(s2);
	if (!(new = malloc(sizeof(char) * (len_1 + len_2 + 1))))
		return (0);
	ft_memcpy((void*)new, (const void*)s1, len_1);
	if (s2)
		ft_memcpy((void*)(new + len_1), (const void*)s2, len_2);
	new[len_1 + len_2] = 0;
	if (s1)
		free(s1);
	return (new);
}

static int	find_next(char *str, int *ret)
{
	int	i;

	i = 0;
	while (*str && *str != '\n')
	{
		++str;
		++i;
	}
	if (*str == '\n')
	{
		*str = 0;
		*ret = 0;
	}
	return (i);
}

static char	*get_line()
{
	char	buff[BUFF_RL + 1];
	char	*str;
	char	*tmp;
	int		ret;
	
	ret = 1;
	buff[BUFF_RL] = 0;
	str = 0;
	tmp = 0;
	while (ret)
	{
		if (0 > (ret = read(0, buff, BUFF_RL)))
			return (0);
		if (!(tmp = malloc(sizeof(char) * (find_next(buff, &ret) + 1))))
			return (0);
		ft_memcpy((void*)tmp, (const void*)buff, ft_strlen(buff));
		tmp[ft_strlen(buff)] = 0;
		str = strjoin_diff(str, tmp);
		free(tmp);
		tmp = 0;
	}
	return (str);
}

char	*ft_readline(char *prompt)
{
    char	*line;

    if (prompt)
    {
        write(STDOUT_FILENO, BLU, ft_strlen(BLU));
        write(STDOUT_FILENO, prompt, ft_strlen(prompt));
		write(STDOUT_FILENO, RESET, ft_strlen(RESET));
        write(STDOUT_FILENO, "$ ", 2);
    }
    line = get_line();
    if (!line)
        return (0);
    return (line);
}