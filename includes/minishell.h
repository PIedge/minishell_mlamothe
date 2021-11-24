/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmerrien <tmerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:16:55 by tmerrien          #+#    #+#             */
/*   Updated: 2021/11/24 10:16:46 by tmerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* *****************************************************************************
**							Includes										  **
*******************************************************************************/

# include <stdio.h>

/* *****************************************************************************
**							Defines											  **
*******************************************************************************/


/*
** The next three defines are used for the variable "type" in the structure
** t_redir described later. The first bit describes wether it is IN or OUT
** (0 == OUT | 1 == IN). TWO decribes wether it is << or < and >> or >
** obviously 0 == < and 1 == <<.
*/
# define IN 1
# define TWO 1 << 1

/* *****************************************************************************
**							Structs											  **
*******************************************************************************/

/*
** The s_redir is a double chained list containing "word" a char* wich is
** the name of the file to redirect to.
** The type variable has been explained above in the Defines section.
*/

typedef struct s_redir
{
	struct s_redir	*next;
	struct s_redir	*prev;

	char			*word;
	int				type;
}					t_redir;

/*
** The s_cmd is a double chained list and behave as a pipe, meaning each element
** of this list is a pipe (ofc if there's only one element then it's not a pipe).
** cmd contains the entire command for the pipe.
** cmd_argv contains arguments for the command behaves like argv in C.
** Well redir is redir.
*/

typedef struct s_cmd
{
	struct s_cmd	*next;
	struct s_cmd	*prev;

	char			*cmd;
	char			**cm_argv;
	t_redir			*redir;
}					t_cmd;

/*
** Main struture for minishell contains every thing that should be freed in case
** of an error.
*/

typedef struct s_mini
{
	t_cmd	*cmd;
}					t_mini;

#endif