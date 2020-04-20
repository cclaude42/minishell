/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:31:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/13 09:21:14 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int ac, char **av, char **env)
{
	int		running;
	char	*command;
	char	**args;

	(void)ac;
	(void)av;
	running = 1;
	while (running)
	{
		write(1, "minishell > ", 13);
		get_next_line(0, &command);
		args = command_parse(command);
		ft_memdel(command);
		if (!args[0] || is_builtin(args, env) || is_bin(args, env))
			;
		else if (ft_strcmp(args[0], "exit") == 0)
			running = 0;
		else
			;
		del_args(args);
	}
	return (0);
}
