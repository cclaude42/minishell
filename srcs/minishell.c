/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:31:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/11 15:36:36 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	int		running;
	char	*command;
	int		i;

	running = 1;
	while (running)
	{
		i = 0;
		write(1, "minishell > ", 13);
		get_next_line(0, &command);
		ft_skip_space(command, &i);
		if ((!ft_strncmp(command + i, "exit", 4)) &&
			(ft_isspacenl(command[i + 4]) || command[i + 4] == '\0'))
			running = 0;
		ft_memdel(command);
	}
	return (0);
}
