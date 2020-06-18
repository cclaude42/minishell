/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:15:54 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/18 17:27:02 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		env_add_back(const char *value, t_env *env)
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

int				ft_export(char **args, t_env *env)
{
	if (!args[1])
		return (0);
	else
	{
		env_add_back(args[1], env);
		while (env && env->next)
			env = env->next;
	}
	return (0);
}