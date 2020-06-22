/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:42:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/22 19:48:52 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int		env_value_size(const char *env)
{
	int		i;
	int		size_name;

	size_name = 0;
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	while (env[i])
	{
		i++;
		size_name++;
	}
	return (size_name);
}

char	*get_env_value(const char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_size(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++]; 
	env_value[i] = '\0';
	return (env_value);
}

char	*env_name_to_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_value;

	while (env)
	{
		get_env_name(env_name, env->value);
		if (arg + 1 != NULL && (ft_strcmp(arg +1, env_name) == 0))
		{
			env_value = get_env_value(env->value);
			return (env_value);
		}
		env = env->next;
	}
	env_value = ft_strdup("\0");
	return (env_value);
}

int		var_size(char *arg, int pos)
{
	int		i;

	i = 0;
	while (arg[pos] && (ft_isalnum(arg[pos]) == 1))
	{
		pos++;
		i++;
	}
	return (i);
}

char	*expansions(char *arg, t_env env)
{
	char	*final_arg;
	int		i;
	int		var_size;

	final_arg = "\0";
	i = 0;
	while (arg[i])
	{
		if (arg[i] = -36)
		{
			i += var_size(arg[i], i);
			final_arg = ft_strjoin(final_arg, env_name_to_value(var, env));
		}
		i++;
	}
}

void	exec_cmd(t_mini *mini, t_token *token)
{
	char	**cmd;
	int		i;

	cmd = cmd_tab(token);
	i = 1;
	while (cmd[i])
	{
		if (cmd[i][0] == -36)
			cmd[i] = env_name_to_value(cmd[i], mini->env);
		i++;
	}
	if (ft_strcmp(cmd[0], "exit") == 0)
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
