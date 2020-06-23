/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:15:54 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/18 18:59:58 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		env_add(const char *value, t_env *env)
{
	t_env	*new;
	t_env	*tmp;

	if (!(new = malloc(sizeof(t_env*))))
		return (-1);
	new->value = ft_strdup(value);
	while (env && env->next && env->next->next)
		env = env->next;
	tmp = env->next;
	env->next = new;
	new->next = tmp;
	return (0);
}

char		*get_env_name(char *dest, const char *src)
{
	int		i;

	i = 0;
	while (src[i] && src[i] != '=')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int				is_in_env(t_env *env, char *args)
{
	char	var_name[BUFF_SIZE];
	char	env_name[BUFF_SIZE];

	get_env_name(var_name, args);
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp(var_name, env_name) == 0)
		{
			free(env->value);
			env->value = ft_strdup(args); 
			return(1);
		}
		env = env->next;
	}
	return(0);
}


int				ft_export(char **args, t_env *env)
{
	int		new_env;

	new_env = 0;
	if (!args[1])
		return (0);
	else
	{
		new_env = is_in_env(env, args[1]);
		if (new_env == 0)
			env_add(args[1], env);
	}
	return (0);
}