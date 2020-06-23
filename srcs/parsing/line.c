/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/23 13:01:56 by cclaude          ###   ########.fr       */
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

int		space_alloc(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (is_sep(line, i))
			count++;
		i++;
	}
	return (i + 2 * count + 1);
}

char	*space_line(char *line)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new = malloc(sizeof(char) * space_alloc(line));
	while (line[i])
	{
		if (open_quotes(line, i) == 0 && is_sep(line, i))
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
	line = space_line(line);
	mini->start = get_tokens(line);
	ft_memdel(line);

	// FOR DEBUGGING
	print_args(mini->start);
}
