/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/23 16:27:35 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	arg_type(t_token *token)
{
	if (ft_strcmp(token->tok, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->tok, ">") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->tok, ">>") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->tok, "<") == 0)
		token->type = REDIR;
	else if (ft_strcmp(token->tok, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->tok, ";") == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= APPEND)
		token->type = CMD;
	else
		token->type = ARG;
}

void	del_args(t_token *start)
{
	while (start->next)
	{
		free(start->tok);
		start = start->next;
		free(start->prev);
	}
	free(start->tok);
	free(start);
}

t_token	*get_next(char *line, int *i)
{
	t_token	*token;
	char	c;
	int		j;

	token = malloc(sizeof(t_token));
	c = ' ';
	if (line[*i] == '\'' || line[*i] == '\"')
		c = line[(*i)++];
	j = 0;
	while (line[*i + j] && line[*i + j] != c)
		j++;
	token->tok = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (line[*i] && line[*i] != c)
		token->tok[j++] = line[(*i)++];
	token->tok[j] = '\0';
	if (line[*i])
		(*i)++;
	return (token);
}

t_token	*get_args(char *line)
{
	t_token	*prev;
	t_token	*next;
	int		i;

	prev = NULL;
	next = NULL;
	i = 0;
	ft_skip_spacenl(line, &i);
	while (line[i])
	{
		next = get_next(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		arg_type(next);
		ft_skip_spacenl(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}
