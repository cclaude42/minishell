/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:31:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 15:07:53 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av, char **env)
{
	int		running;
	char	*command;
	char	**args;

	(void)ac;
	(void)av;
	running = 1;
	while (running)
	{
		i = 0;
		write(1, "minishell > ", 13);
		get_next_line(0, &command);
		// args = parsing(command);
		args = {"ls", "-l", NULL}
		//
		ft_memdel(command);
		if (is_builtin(args, env))
			;
		else if (is_bin(args, env))
			;
		else if (is_exit(args))
			running = 0;
		else
			write(2, "Error", 5);
		// ft_memdel_loop(argv);
	}
	return (0);
}
