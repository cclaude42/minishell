/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:20:13 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/09 16:58:11 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>

int	main(void)
{
	pid_t	pid;
	int		pipefd[2];
	char	buf[4096];
	int		ret;
	int		save;
	int		fd;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		while ((ret = read(pipefd[0], &buf, 4095)) > 0)
			write(1, &buf, ret);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		save = dup(1);
		fd = open("file.txt", O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
		dup2(pipefd[1], 1);
		system("ls -la");
		dup2(save, 1);
		close(save);
		close(pipefd[1]);
	}
	return (0);
}
