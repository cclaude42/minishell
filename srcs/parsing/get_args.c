/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/21 00:18:31 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

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

t_token	*get_next(char *cmd_line, int *i)
{
	t_token	*token;
	char	c;
	int		j;

	token = malloc(sizeof(t_token));
	c = ' ';
	if (cmd_line[*i] == '\'' || cmd_line[*i] == '\"')
		c = cmd_line[(*i)++];
	j = 0;
	while (cmd_line[*i + j] != c)
		j++;
	token->tok = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (cmd_line[*i] != c)
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
		arg_type(next);
	}
	next->next = NULL;
	while (next->prev)
		next = next->prev;
	return (next);
}

int	main(void)
{
	t_token	*list;
	int		i = 1;

	list = get_args("ls");
	while (list->next)
	{
		printf("#%d %s\n", i, list->tok);
		free(list->tok);
		list = list->next;
		free(list->prev);
		i++;
	}
	printf("#%d %s\n", i, list->tok);
	free(list->tok);
	free(list);
}
