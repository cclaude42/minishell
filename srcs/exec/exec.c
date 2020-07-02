/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:42:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/07/02 16:48:25 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_exit(t_token *token, char *cmd)
{
	t_token	*tmp;
	int		pipe;

	tmp = token;
	pipe = 0;
	while (tmp && is_type(tmp, END) == 0)
	{
		if (is_type(tmp, PIPE))
			pipe = 1;
		tmp = tmp->next;
	}
	if (ft_strcmp(cmd, "exit") == 0 && pipe == 0)
		return (1);
	return (0);
}

char	**cmd_tab(t_token *start)
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

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

	cmd = cmd_tab(token);
	i = 1;
	while (cmd[i])
	{
		cmd[i] = expansions(cmd[i], mini->env);
		i++;
	}
	if (is_exit(token, cmd[0]))
		mini->run = 0;
	if (is_builtin(cmd[0]))
		exec_builtin(cmd, mini);
	else
		exec_bin(cmd, mini->env);
	ft_memdel(cmd);
	close(mini->pipin);
	close(mini->pipout);
	mini->pipin = -1;
	mini->pipout = -1;
}
