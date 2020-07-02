/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 17:40:30 by macrespo          #+#    #+#             */
/*   Updated: 2020/07/02 17:51:25 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_env_char(int c)
{
	if (ft_isalnum(c) == 1 || c == '_')
		return(1);
	return (0);
}

int		env_value_len(const char *env)
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

char	*env_value(char *env)
{
	int		i;
	int		j;
	int		size_alloc;
	char	*env_value;

	size_alloc = env_value_len(env) + 1;
	if (!(env_value = malloc(sizeof(char) * size_alloc)))
		return (NULL);
	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	i += 1;
	j = 0;
	while (env[i])
		env_value[j++] = env[i++];
	env_value[j] = '\0';
	return (env_value);
}

char	*get_env_value(char *arg, t_env *env)
{
	char	env_name[BUFF_SIZE];
	char	*env_val;

	while (env)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(arg, env_name) == 0)
		{
			env_val = env_value(env->value);
			return (env_val);
		}
		env = env->next;
	}
	env_val = ft_strdup("\n");
	return (env_val);
}
