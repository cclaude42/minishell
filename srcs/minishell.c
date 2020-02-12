/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:31:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 11:14:42 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		magic_box(char *command, int start_pos, char **env)
{
	char *arg[] = {"ls", "-l", NULL};
	pid_t pid;

	if (ft_strncmp(command + start_pos, "ls", 4) == 0)
	{
		pid = fork();
		if (pid == 0)
			execve("/bin/ls", arg, env);
		else
			wait(&pid);
	}
}

int	main(int argc, char **argv, char **env)
{
	int		running;
	char	*command;
	int		i;

	(void)argc;
	(void)argv;
	running = 1;
	while (running)
	{
		i = 0;
		write(1, "minishell > ", 13);
		get_next_line(0, &command);
		ft_skip_space(command, &i);
		magic_box(command, i, env);
		if ((!ft_strncmp(command + i, "exit", 4)) &&
			(ft_isspacenl(command[i + 4]) || command[i + 4] == '\0'))
			running = 0;
		ft_memdel(command);
	}
	return (0);
}
