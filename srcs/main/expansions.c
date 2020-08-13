/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 16:06:28 by macrespo          #+#    #+#             */
/*   Updated: 2020/08/13 15:46:11 by cclaude          ###   ########.fr       */
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
	if (ft_isdigit(arg[pos]))
		return (0);
	while (arg[pos] && is_env_char(arg[pos]) == 1 && i < BUFF_SIZE)
	{
		var_name[i] = arg[pos];
		pos++;
		i++;
	}
	var_name[i] = '\0';
	var_value = get_env_value(var_name, env);
	i = ft_strlen(var_value);
	ft_memdel(var_value);
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
			if (arg[i] == '\0' || ft_isalnum(arg[i]) == 0)
				size++;
			else
				size += get_var_len(arg, i, env);
			if (ft_isdigit(arg[i]) == 0)
			{
				while (is_env_char(arg[i]))
				i++;
			}
			else
				size--;
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
	if (ft_isdigit(arg[pos]))
		return (NULL);
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
	char	*new_arg;
	int		i;
	int		j;
	char	*env_value;

	if (!(new_arg = malloc(sizeof(char) * arg_alloc_len(arg, env))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < arg_alloc_len(arg, env) && arg[j])
	{
		while (arg[j] == EXPANSION)
		{
			j++;
			if ((arg[j] == '\0' || ft_isalnum(arg[j]) == 0) && arg[j] != '?')
				new_arg[i++] = '$';
			else
			{
				env_value = get_var_value(arg, j, env, ret);
				i += env_value ? varlcpy(new_arg, env_value, i) : 0;
				arg[j] == '?' ? j++ : 0;
				if (ft_isdigit(arg[j]) == 0)
				{
					while (is_env_char(arg[j]) == 1)
						j++;
				}
				else
					j++;
			}
		}
		new_arg[i++] = arg[j++];
	}
	new_arg[i] = 0;
	return (new_arg);
}
