/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 11:51:22 by cclaude           #+#    #+#             */
/*   Updated: 2020/07/05 18:27:28 by anonymous        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_and_exec(t_mini *mini, t_token *token)
{
	t_token	*prev;
	t_token	*next;
	int		pipe;

	prev = prev_sep(token, NOSKIP);
	next = next_sep(token, NOSKIP);
	pipe = 0;
	if (is_type(prev, TRUNC))
		redir(mini, token, TRUNC);
	else if (is_type(prev, APPEND))
		redir(mini, token, APPEND);
	else if (is_type(prev, INPUT))
		input(mini, token);
	else if (is_type(prev, PIPE))
		pipe = minipipe(mini);
	if (next && is_type(next, END) == 0 && pipe != 1)
		redir_and_exec(mini, next->next);
	if ((is_type(prev, END) || is_type(prev, PIPE) || !prev) && pipe != 1)
		exec_cmd(mini, token);
	if (pipe == 2)
		exit(0);
}

void	minishell(t_mini *mini)
{
	t_token	*token;
	pid_t	pid;
	int		status;

	token = next_run(mini->start, NOSKIP);
	while (mini->run && is_type(token, CMD))
	{
		pid = (has_pipe(token)) ? fork() : 1;
		if (pid == 0 || pid == 1)
			redir_and_exec(mini, token);
		else
			waitpid(pid, &status, 0);
		if (pid == 0)
			exit(ft_abs(mini->run - 1));
		reset_std(mini);
		close_fds(mini);
		waitpid(mini->pid, NULL, 0);
		reset_fds(mini);
		token = next_run(token, SKIP);
	}
	// if (WEXITSTATUS(status) != 0)
	// 	exit(0);
}

int		main(int ac, char **av, char **env)
{
	t_mini	mini;

	(void)ac;
	(void)av;
	mini.in = dup(STDIN);
	mini.out = dup(STDOUT);
	mini.run = 1;
	reset_fds(&mini);
	env_init(&mini, env);
	while (mini.run)
	{
		parse(&mini);
		if (mini.start != NULL)
			minishell(&mini);
		free_token(mini.start);
	}
	return (0);
}
