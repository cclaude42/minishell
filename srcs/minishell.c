/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:51:22 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/09 13:44:42 by cclaude          ###   ########.fr       */
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
	while (token && token->type < TRUNC)
	{
		token = token->next;
		i++;
	}
	tab = malloc(sizeof(char *) * i);
	token = start->next;
	tab[0] = start->str;
	i = 1;
	while (token && token->type < TRUNC)
	{
		tab[i] = token->str;
		token = token->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	run_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;

	cmd = get_cmd_tab(token);
	if (ft_strcmp(cmd[0], "exit") == 0)
		mini->run = 0;
	bin_exec(cmd, mini->env);
	ft_memdel(cmd);
}

void	redirect(t_mini *mini, t_token *token, int std, int trunc)
{
	t_token	*tmp;
	int		save;
	int		fd;

	save = dup(std);
	tmp = token;
	while (tmp && tmp->type < TRUNC)
		tmp = tmp->next;
	if (trunc)
		fd = open(tmp->next->str, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else
		fd = open(tmp->next->str, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	dup2(fd, std);
	run_cmd(mini, token);
	dup2(save, std);
	close(save);
	close(fd);
}

// void	minipipe(t_mini *mini, t_token *token)
// {
	// pid_t	pid;
	// t_token	*tmp;
	// int		save;
	//
	// tmp = token->next;
	// while (tmp && tmp->type != CMD)
	// 	tmp = tmp->next;
	// save = dup(STDOUT);
	// dup2(STDIN, STDOUT);
	// pid = fork();
	// if (pid == 0)
	// {
		// run_cmd(mini, tmp);
	// 	exit(0);
	// }
	// else
// 		run_cmd(mini, token);
// 	dup2(save, STDOUT);
// 	close(save);
// }

void	minipipe(t_mini *mini, t_token *token)
{
	t_token	*tmp;
	pid_t	pid;
	int		pipefd[2];
	int		save;

	tmp = token->next;
	while (tmp && tmp->type != CMD)
		tmp = tmp->next;
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		save = dup(STDIN);
		dup2(pipefd[0], STDIN);
		run_cmd(mini, tmp);
		dup2(save, STDIN);
		close(save);
		close(pipefd[0]);
		exit(0);
	}
	else
	{
		close(pipefd[0]);
		save = dup(STDOUT);
		dup2(pipefd[1], STDOUT);
		run_cmd(mini, token);
		dup2(save, STDOUT);
		close(save);
		close(pipefd[1]);
	}
}

void	check_redir(t_mini *mini, t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp && tmp->type < TRUNC)
		tmp = tmp->next;
	if (tmp && tmp->type == TRUNC)
		redirect(mini, token, STDOUT, 1);
	else if (tmp && tmp->type == APPEND)
		redirect(mini, token, STDOUT, 0);
	else if (tmp && tmp->type == INPUT)
		redirect(mini, token, STDIN, 0);
	else if (token && token->type == PIPE)
		minipipe(mini, token);
	else
		run_cmd(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;

	token = mini->start;
	while (token && token->type != CMD)
		token = token->next;
	while (mini->run && token && token->type == CMD)
	{
		check_redir(mini, token);
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
