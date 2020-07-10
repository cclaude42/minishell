/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:37:17 by cclaude           #+#    #+#             */
/*   Updated: 2020/07/10 16:26:08 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		magic_box(char *path, char **args, t_env *env)
{
	pid_t	pid;
	char	**env_array;
	int		ret;

	pid = fork();
	ret = 0;
	if (pid == 0)
	{
		env_array = ft_split(env_to_str(env), '\n');
		ret = execve(path, args, env_array);
		free_tab(env_array);
	}
	else
		waitpid(pid, NULL, 0);
	return (ret);
}

char	*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char	*check_dir(char *bin, char *command)
{
	DIR				*folder;
	struct dirent	*item;
	char			*path;

	path = NULL;
	folder = opendir(bin);
	if (!folder)
		return (NULL);
	while ((item = readdir(folder)))
	{
		if (ft_strcmp(item->d_name, command) == 0)
			path = path_join(bin, item->d_name);
	}
	closedir(folder);
	return (path);
}

int		exec_bin(char **args, t_env *env)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = 1;
	while (env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env->next == NULL)
		return (ret);
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ret);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (bin[i] == NULL)
	{
		free_tab(bin);
		return (0);
	}
	ret = magic_box(path, args, env);
	ft_memdel(path);
	free_tab(bin);
	return (ret);
}
