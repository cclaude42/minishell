/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/20 20:07:26 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_next(char *cmd_line, int *i)
{
	t_token	*token;
	int		j;

	j = 0;
	token = malloc(sizeof(t_token));
	token->tok = malloc(SIZEOF ARG);
	while (cmd_line[*i] != ' ')
		token->tok[j++] = cmd_line[(*i)++];
	return (token);
}

t_token	*get_args(char *cmd_line)
{
	t_token	*prev;
	t_token	*next;
	int		i;

	prev = NULL;
	i = 0;
	while (cmd_line[i])
	{
		next = get_next(cmd_line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
	}
	next->next = NULL;
	while (next->prev)
		next = next->prev;
	return (next);
}
