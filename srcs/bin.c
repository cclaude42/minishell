/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:07:01 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 16:51:52 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	magic_box(char *path, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(path, args, env);
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
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
		{
			tmp = ft_strjoin(bin, "/");
			path = ft_strjoin(tmp, item->d_name);
			ft_memdel(tmp);
		}
	}
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
	bin = ft_split(env[i], ':');
	if (!args[0] && !bin[0])
		return (-1);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (bin[i] == NULL)
		return (0);
	magic_box(path, args, env);
	ft_memdel(path);
	return (1);
}
