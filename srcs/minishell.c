/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:51:22 by cclaude           #+#    #+#             */
/*   Updated: 2020/05/23 13:33:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	magic_box(char *path, char **args, char **env)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
		execve(path, args, env);
	else
		wait(&pid);
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

int		bin_exec(char **args, char **env)
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
	{
		del_tab(bin);
		return (0);
	}
	magic_box(path, args, env);
	ft_memdel(path);
	del_tab(bin);
	return (1);
}

char	**get_cmd_tab(t_token *start)
{
	t_token	*token;
	char	**tab;
	int		i;

	token = start->next;
	i = 2;
	while (token && token->type < APPEND)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < APPEND)
	{
		tab[i] = token->str;
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	minishell(t_mini *mini)
{
	char	**cmd;
	t_token	*token;

	token = mini->start;
	while (token && token->type != CMD)
		token = token->next;
	while (token && token->type == CMD)
	{
		cmd = get_cmd_tab(token);
		if (ft_strcmp(cmd[0], "exit") == 0)
		{
			mini->run = 0;
			return ;
		}
		bin_exec(cmd, mini->env);
		ft_memdel(cmd);
		token = token->next;
		while (token && token->type != CMD)
			token = token->next;
	}
}

int		main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.env = env;
	mini.run = 1;
	while (mini.run)
	{
		parse(&mini);
		if (mini.start != NULL)
			minishell(&mini);
		del_args(mini.start);
	}
	return (0);
}
