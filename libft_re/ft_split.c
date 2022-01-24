/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlamothe <mlamothe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/11 18:29:50 by mlamothe          #+#    #+#             */
/*   Updated: 2022/01/24 12:56:34 by mlamothe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_re.h"

int	calc_words(char *str, char c)
{
	int	i;
	int	nb;

	i = -1;
	nb = 0;
	while (str[++i])
	{
		while (str[i] && str[i] == c)
			i++;
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == 0)
			i--;
		nb++;
	}
	return (nb + 1);
}

int	size_word(char *str, char c, int i)
{
	int	s_word;

	s_word = 0;
	while (str[i] && str[i] != c)
	{
		s_word++;
		i++;
	}
	return (s_word);
}

char	*crea_word(char *str, char c, int *i)
{
	char	*word;
	int		s_word;
	int		j;

	s_word = size_word(str, c, *i);
	word = malloc((s_word + 1) * sizeof(char));
	if (!(word))
		return (NULL);
	j = -1;
	while (++j < s_word)
	{
		word[j] = str[*i];
		(*i)++;
	}
	word[j] = 0;
	return (word);
}

char	**ft_split(char *str, char c)
{
	int		i;
	char	**all_w;
	int		nbwords;

	i = -1;
	nbwords = 0;
	all_w = (char **)malloc(calc_words(str, c) * sizeof(char *));
	if (str == NULL || !(all_w))
		return (NULL);
	while (str[++i])
	{
		while (str[i] == c)
			i++;
		if (str[i])
		{
			all_w[nbwords] = crea_word(str, c, &i);
			if (!(all_w[nbwords]))
				return (NULL);
			nbwords++;
		}
		i--;
	}
	all_w[nbwords] = 0;
	return (all_w);
}
