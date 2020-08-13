/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/20 19:41:37 by cclaude           #+#    #+#             */
/*   Updated: 2020/08/13 15:36:37 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if (open_quotes(line, i) != 2 && line[i] == '$')
			new[j++] = (char)(-line[i++]);
		else
			new[j++] = line[i++];
	}
	new[j] = '\0';
	ft_memdel(line);
	return (new);
}

void	quote_loop(char **line)
{
	char	*more;
	char	*tmp;

	while (open_quotes(*line, 2147483647))
	{
		ft_putstr_fd("\033[0;36m> \033[0m", STDERR);
		get_next_line(0, &more);
		tmp = *line;
		*line = ft_strjoin(*line, "\n");
		ft_memdel(tmp);
		tmp = *line;
		*line = ft_strjoin(*line, more);
		ft_memdel(tmp);
		ft_memdel(more);
	}
}

void	parse(t_mini *mini)
{
	char	*line;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	ft_putstr_fd("\033[0;36mminishell > \033[0m", STDERR);
	if (get_next_line(0, &line) == -2)
	{
		mini->exit = 1;
		ft_putendl_fd("exit", STDERR);
	}
	if (g_sig.sigint == 1)
		mini->ret = g_sig.exit_status;
	quote_loop(&line);
	line = space_line(line);
	mini->start = get_tokens(line);
	ft_memdel(line);
	squish_args(mini);
}
