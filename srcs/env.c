/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:01:42 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/09 16:58:45 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	lst_init(t_mini *mini, char **env)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (env = malloc(sizeof(t_env*)))
		return (NULL);
	env->value = ft_strdup(env[0]);
	env->next = NULL;
	mini->first = env;
	i = 1;
	while (env[i])
	{
		if (new = malloc(sizeof(t_env*)))
			return (NULL);
		new->value = ft_strdup(env[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
}