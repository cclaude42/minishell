/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:51:22 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/10 16:49:34 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_type(t_token *token, int type)
{
	if (token && token->type == type)
		return (1);
	else
		return (0);
}

t_token	*next_type(t_token *token, int type, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != type)
		token = token->next;
	return (token);
}

t_token	*next_sep(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type < TRUNC)
		token = token->next;
	return (token);
}

t_token	*next_run(t_token *token, int skip)
{
	if (token && skip)
		token = token->next;
	while (token && token->type != CMD)
	{
		token = token->next;
		if (token && token->type == CMD && token->prev == NULL)
			;
		else if (token && token->type == CMD && token->prev->type < END)
			token = token->next;
	}
	return (token);
}

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
	tmp = next_type(token, CMD, SKIP);
	if (trunc)
		fd = open(tmp->str, O_CREAT | O_RDWR | O_TRUNC, S_IRWXU);
	else
		fd = open(tmp->str, O_CREAT | O_RDWR | O_APPEND, S_IRWXU);
	dup2(fd, std);
	run_cmd(mini, token);
	dup2(save, std);
	close(save);
	close(fd);
}

void	pipe_end(t_mini *mini, t_token *token, int fd, int std)
{
	int	save;

	save = dup(std);
	dup2(fd, std);
	run_cmd(mini, token);
	dup2(save, std);
	close(save);
	close(fd);
	if (std == STDIN)
		exit(0);
	else
		wait(NULL);
}

void	minipipe(t_mini *mini, t_token *token)
{
	t_token	*tmp;
	pid_t	pid;
	int		pipefd[2];

	tmp = next_type(token, CMD, SKIP);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[1]);
		pipe_end(mini, tmp, pipefd[0], STDIN);
	}
	else
	{
		close(pipefd[0]);
		pipe_end(mini, token, pipefd[1], STDOUT);
	}
}

void	check_redir(t_mini *mini, t_token *token)
{
	t_token	*tmp;

	tmp = next_sep(token, NOSKIP);
	if (is_type(tmp, TRUNC))
		redirect(mini, token, STDOUT, 1);
	else if (is_type(tmp, APPEND))
		redirect(mini, token, STDOUT, 0);
	else if (is_type(tmp, INPUT))
		redirect(mini, token, STDIN, 0);
	else if (is_type(tmp, PIPE))
		minipipe(mini, token);
	else
		run_cmd(mini, token);
}

void	minishell(t_mini *mini)
{
	t_token	*token;

	token = next_run(mini->start, NOSKIP);
	while (mini->run && is_type(token, CMD))
	{
		check_redir(mini, token);
		token = next_run(mini->start, SKIP);
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
