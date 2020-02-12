/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:07:01 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 15:07:45 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	magic_box(char *path, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(path, arg, env);
	else
		wait(&pid);
}

static char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*tmp;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	while ((item = readdir(rep)) != NULL)
		if (strncmp(item->d_name, command, strlen(command) + 1) == 0)
		{
			tmp = ft_strjoin(item->d_name, "/");
			path = ft_strjoin(tmp, command);
			free(tmp);
		}
		free(item);
	closedir(folder);
	return (path);
}

int			is_bin(char **args, char **env)
{
	int		i;
	char	**bin;
	char	*path;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] == NULL)
		return (-1);
	i = 0
	bin = ft_split(env[i], ":");
	while (bin[i] && (path = check_dir(bin[i], args[0])) == NULL)
		i++;
	if (bin[i] == NULL)
		return (0);
	magic_box(path, args, env);
	return (1);
}
