/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:37:17 by cclaude           #+#    #+#             */
/*   Updated: 2020/08/06 15:38:09 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			error_message(char *path)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_WRONLY);
	folder = opendir(path);
	if (ft_strchr(path, '/') == NULL)
		ft_printf("minishell: %s: command not found\n", path);
	else if (fd == -1 && folder == NULL)
		ft_printf("minishell: %s: No such file or directory\n", path);
	else if (fd == -1 && folder != NULL)
		ft_printf("minishell: %s: is a directory\n", path);
	else if (fd != -1 && folder == NULL)
		ft_printf("minishell: %s: Permission denied\n", path);
	if (ft_strchr(path, '/') == NULL || (fd == -1 && folder == NULL))
		ret = UNKNOWN_COMMAND;
	else
		ret = IS_DIRECTORY;
	if (folder)
		closedir(folder);
	close(fd);
	return (ret);
}

int			magic_box(char *path, char **args, t_env *env)
{
	char	**env_array;
	int		ret;

	ret = SUCCESS;
	g_sig.pid = fork();
	if (g_sig.pid == 0)
	{
		env_array = ft_split(env_to_str(env), '\n');
		if (ft_strchr(path, '/') != NULL)
			execve(path, args, env_array);
		ret = error_message(path);
		free_tab(env_array);
		exit(ret);
	}
	else
		waitpid(g_sig.pid, &ret, 0);
	if (g_sig.sigint == 1 || g_sig.sigquit == 1)
		return (g_sig.exit_status);
	ret = (ret == 32256 || ret == 32512) ? ret / 256 : !!ret;
	return (ret);
}

char		*path_join(const char *s1, const char *s2)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(s1, "/");
	path = ft_strjoin(tmp, s2);
	ft_memdel(tmp);
	return (path);
}

char		*check_dir(char *bin, char *command)
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

int			exec_bin(char **args, t_env *env)
{
	int		i;
	char	**bin;
	char	*path;
	int		ret;

	i = 0;
	ret = UNKNOWN_COMMAND;
	while (env->value && ft_strncmp(env->value, "PATH=", 5) != 0)
		env = env->next;
	if (env->next == NULL)
		return (ERROR);
	bin = ft_split(env->value, ':');
	if (!args[0] && !bin[0])
		return (ERROR);
	i = 1;
	path = check_dir(bin[0] + 5, args[0]);
	while (args[0] && bin[i] && path == NULL)
		path = check_dir(bin[i++], args[0]);
	if (path != NULL)
		ret = magic_box(path, args, env);
	else
		ret = magic_box(args[0], args, env);
	free_tab(bin);
	ft_memdel(path);
	return (ret);
}
