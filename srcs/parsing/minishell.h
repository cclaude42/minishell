/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:53 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/20 20:02:59 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

# define EMP 0
# define CMD 1
# define ARG 2
# define REDIR 3
# define PIPE 4
# define ENV 5
# define END 6

typedef struct	s_mini
{
	t_token			*start;
}				t_mini;

typedef struct	s_token
{
	char			*tok;
	int				type;
	t_token			*prev;
	t_token			*next;
}				t_token;

#endif
