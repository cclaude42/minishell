/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/09 15:52:08 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_args(t_token *start)
{
	int		i = 0;
	char	*s[8] = {"(EMPTY)", "(CMD)", "(ARG)", "(TRUNC)",
					"(APPEND)", "(INPUT)", "(PIPE)", "(END)"};

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

int		open_quotes(char *line, int index)
{
	int	i;
	int	open;

	i = 0;
	open = 0;
	while (line[i] && i != index)
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

int		space_args_alloc(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (open_quotes(line, i) == 0 && ft_strchr("<>|;", line[i]))
			count++;
		i++;
	}
	return (i + 2 * count + 1);
}

char	*space_args(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * space_args_alloc(line));
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

int		get_next_alloc(char *line, int *i)
{
	int		count;
	int		j;
	char	c;

	count = 0;
	j = 0;
	c = ' ';
	while (line[*i + j] && (line[*i + j] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i + j] == '\'' || line[*i + j] == '\"'))
			c = line[*i + j++];
		else if (c != ' ' && line[*i + j] == c)
		{
			count += 2;
			c = ' ';
			j++;
		}
		else
			j++;
	}
	return (j - count + 1);
}

t_token	*get_next(char *line, int *i)
{
	t_token	*token;
	int		j;
	char	c;

	j = 0;
	c = ' ';
	token = malloc(sizeof(t_token));
	token->str = malloc(sizeof(char) * get_next_alloc(line, i));
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

void	parse(t_mini *mini)
{
	char	*line;
	char	*more;
	char	*tmp;

	write(1, "minishell > ", 13);
	get_next_line(0, &line);
	while (open_quotes(line, 214748364))
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
	line = space_args(line);
	mini->start = get_args(line);
	ft_memdel(line);

	// FOR DEBUGGING
	print_args(mini->start);
}
