/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:28 by macrespo          #+#    #+#             */
/*   Updated: 2020/07/02 17:25:00 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

static int		env_value_len(const char *env)
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

static char	*env_value(char *env)
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

static char	*get_env_value(char *arg, t_env *env)
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

static int		get_var_len(const char *arg, int pos, t_env *env)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	while (arg[pos] && (ft_isalnum(arg[pos]) == 1 || arg[pos] == '_') && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	free(var_value);
	return (i);
}

static int		arg_alloc_len(const char *arg, t_env *env)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (arg[i] == EXPANSION)
		{
			i++;
			size += get_var_len(arg, i, env);
			while (ft_isalnum(arg[i]) == 1 || arg[i] == '_')
				i++;
		}
		i++;
		size++;
	}
	return (size);
}

static char		*get_var_value(const char *arg, int pos, t_env *env)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	while (arg[pos] && (ft_isalnum(arg[pos]) || arg[pos] == '_') == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	return (var_value);
}

static int		varlcpy(char *new_arg, const char *env_value, int pos)
{
	int		i;

	i = 0;
	while (env_value[i])
		new_arg[pos++] = env_value[i++];
	return (i);
}

char			*expansions(const char *arg, t_env *env)
{
	int		size;
	char	*new_arg;
	int		i;
	int		j;
	char	*env_value;

	size = arg_alloc_len(arg, env);
	if (!(new_arg = malloc(sizeof(char) * size)))
		return (NULL);
	i = 0;
	j = 0;
	while (i < size && arg[j])
	{
		if (arg[j] == EXPANSION)
		{
			j++;
			env_value = get_var_value(arg, j, env); 
			i += varlcpy(new_arg, env_value, i);
			while (ft_isalnum(arg[j]) || arg[j] == '_')
				j++;
		}
		new_arg[i++] = arg[j++];
	}
	new_arg[i] = 0;
	return (new_arg);
}
