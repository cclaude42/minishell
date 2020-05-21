/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/21 14:45:40 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_token *start)
{
	int		i = 0;
	char	*s[8] = {"(EMPTY)", "(CMD)", "(ARG)", "(APPEND)",
					"(TRUNC)", "(REDIR)", "(PIPE)", "(END)"};

	while (start->next)
	{
		printf("#%d %-8s [%s]\n", i++, s[start->type], start->str);
		start = start->next;
	}
	printf("#%d %-8s [%s]\n", i++, s[start->type], start->str);
}

void	arg_type(t_token *token)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = REDIR;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= APPEND)
		token->type = CMD;
	else
		token->type = ARG;
}

void	del_args(t_token *start)
{
	while (start && start->next)
	{
		free(start->str);
		start = start->next;
		free(start->prev);
	}
	if (start)
	{
		free(start->str);
		free(start);
	}
}

void	del_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
	token->str = malloc(sizeof(char) * (j + 1));
	j = 0;
	while (line[*i] && line[*i] != c)
		token->str[j++] = line[(*i)++];
	token->str[j] = '\0';
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
	ft_skip_space(line, &i);
	while (line[i])
	{
		next = get_next(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		arg_type(next);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

int		open_quotes(char *line)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i])
	{
		if (open == 0 && line[i] == '\"')
			open = 1;
		else if (open == 0 && line[i] == '\'')
			open = 2;
		else if (open == 1 && line[i] == '\"')
			open = 0;
		else if (open == 2 && line[i] == '\'')
			open = 0;
		i++;
	}
	return (open);
}

void	parse(t_mini *mini)
{
	char	*line;
	char	*more;
	char	*tmp;

	write(1, "minishell > ", 13);
	get_next_line(0, &line);
	while (open_quotes(line))
	{
		write(1, "> ", 2);
		get_next_line(0, &more);
		tmp = line;
		line = ft_strjoin(line, "\n");
		ft_memdel(tmp);
		tmp = line;
		line = ft_strjoin(line, more);
		ft_memdel(more);
		ft_memdel(tmp);
	}
	mini->start = get_args(line);
	ft_memdel(line);
	// print_args(mini->start);
}
