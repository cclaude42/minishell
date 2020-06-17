/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/17 15:33:40 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_token *start)
{
	int		i = 0;
	char	*s[8] = {"(EMPTY)", "(CMD)", "(ARG)", "(TRUNC)",
					"(APPEND)", "(INPUT)", "(PIPE)", "(END)"};

	if (!start)
		return ;
	while (start->next)
	{
		printf("\033[0;33m#%d %-8s [%s]\033[0m\n", i++, s[start->type], start->str);
		start = start->next;
	}
	printf("\033[0;33m#%d %-8s [%s]\033[0m\n", i++, s[start->type], start->str);
}

void	type_arg(t_token *token)
{
	if (ft_strcmp(token->str, "") == 0)
		token->type = EMPTY;
	else if (ft_strcmp(token->str, ">") == 0)
		token->type = TRUNC;
	else if (ft_strcmp(token->str, ">>") == 0)
		token->type = APPEND;
	else if (ft_strcmp(token->str, "<") == 0)
		token->type = INPUT;
	else if (ft_strcmp(token->str, "|") == 0)
		token->type = PIPE;
	else if (ft_strcmp(token->str, ";") == 0)
		token->type = END;
	else if (token->prev == NULL || token->prev->type >= TRUNC)
		token->type = CMD;
	else
		token->type = ARG;
}

char	*space_args(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * space_alloc(line));
	while (line[i])
	{
		if (open_quotes(line, i) == 0 && ft_strchr("<>|;", line[i]))
		{
			new[j++] = ' ';
			new[j++] = line[i++];
			if (open_quotes(line, i) == 0 && line[i] == '>')
				new[j++] = line[i++];
			new[j++] = ' ';
		}
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

t_token	*next_arg(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(char) * next_alloc(line, i));
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else
			token->str[j++] = line[(*i)++];
	}
	token->str[j] = '\0';
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
		next = next_arg(line, &i);
		next->prev = prev;
		if (prev)
			prev->next = next;
		prev = next;
		type_arg(next);
		ft_skip_space(line, &i);
	}
	if (next)
		next->next = NULL;
	while (next && next->prev)
		next = next->prev;
	return (next);
}

void	parse(t_mini *mini)
{
	char	*line;
	char	*more;
	char	*tmp;

	ft_printf("\033[0;36mminishell > \033[0m");
	get_next_line(0, &line);
	while (open_quotes(line, 2147483647))
	{
		ft_printf("\033[0;36m> \033[0m");
		get_next_line(0, &more);
		tmp = line;
		line = ft_strjoin(line, "\n");
		ft_memdel(tmp);
		tmp = line;
		line = ft_strjoin(line, more);
		ft_memdel(tmp);
		ft_memdel(more);
	}
	line = space_args(line);
	mini->start = get_args(line);
	ft_memdel(line);

	// FOR DEBUGGING
	print_args(mini->start);
}
