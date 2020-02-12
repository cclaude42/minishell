/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:31:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 13:58:52 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		magic_box(char *path, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(path, arg, env);
	else
		wait(&pid);
}

int	main(int argc, char **argv, char **env)
{
	int		running;
	char	*command;
	char	**args;

	(void)argc;
	(void)argv;
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
		if (magic_box(args, env))
			;
		else if (magic_box2(args, env))
			;
		else if (is_exit(args))
			running = 0;
		else
			write(2, "Error", 5);
		printf("ECHO BRANCH\n");
		// ft_memdel_loop(argv);
	}
	return (0);
}
