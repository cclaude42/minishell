/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:53 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/19 15:34:28 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stdbool.h>

# define EMPTY 0
# define CMD 1
# define ARG 2
# define APPEND 3
# define TRUNC 4
# define REDIR 5
# define PIPE 6
# define END 7

typedef struct	s_token
{
	char			*tok;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct	s_mini
{
	t_token			*start;
	int				run;
}				t_mini;

t_token			*get_args(char *line);
void			del_args(t_token *start);

#endif
