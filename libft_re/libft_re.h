/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_re.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:37:05 by tmerrien          #+#    #+#             */
/*   Updated: 2021/12/12 21:15:36 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_RE_H
# define LIBFT_RE_H

# include <stdio.h>

/*
** Defines, all of them are explicit
*/
# ifndef COLORS
#  define COLORS
#  define BLU "\033[34m"
#  define RED "\033[31m"
#  define GRN "\033[32m"
#  define RESET "\033[0m" 
# endif

# ifndef BUFF_RL
#  define BUFF_RL 200
# endif

/*
** Clasic functions
*/

size_t	ft_strlen(char *s);
void	*ft_strcpy(char *dest, const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_isalpha(int c);
int		ft_isdigit(int c);

/*
** New functions
*/

char	*ft_readline(char *prompt);
void	ft_printf_double_tab(char **av, char *name);
void	ft_double_tab_free(char **tab);
int		ft_is_white_space(char c);

#endif
