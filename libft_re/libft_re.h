/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_re.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 11:37:05 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/25 12:06:45 by tmerrien         ###   ########.fr       */
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

#endif
