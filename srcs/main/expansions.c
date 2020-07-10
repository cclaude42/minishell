/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:28 by macrespo          #+#    #+#             */
/*   Updated: 2020/07/10 15:01:15 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_var_len(const char *arg, int pos, t_env *env)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
		return (1);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
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
			while (is_env_char(arg[i]))
				i++;
		}
		i++;
		size++;
	}
	return (size);
}

static char		*get_var_value(const char *arg, int pos, t_env *env, int ret)
{
	char	var_name[BUFF_SIZE];
	char	*var_value;
	int		i;

	i = 0;
	if (arg[pos] == '?')
	{
		var_value = ft_itoa(ret);
		return (var_value);
	}
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
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

char			*expansions(const char *arg, t_env *env, int ret)
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
		while (arg[j] == EXPANSION)
		{
			j++;
			env_value = get_var_value(arg, j, env, ret);
			if (env_value)
				i += varlcpy(new_arg, env_value, i);
			if (arg[j] == '?')
				j++;
			while (is_env_char(arg[j]) == 1)
				j++;
		}
		new_arg[i++] = arg[j++];
	}
	new_arg[i] = 0;
	return (new_arg);
}
