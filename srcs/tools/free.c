/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/17 15:55:31 by cclaude           #+#    #+#             */
/*   Updated: 2020/06/17 16:18:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_token *start)
{
	while (start && start->next)
	{
		free(start->str);
		start = start->next;
		free(start->prev);
	}
	if (start)
	{
		free(start->str);
		free(start);
	}
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env && env->next)
	{
		tmp = env;
		env = env->next;
		free(tmp->value);
		free(tmp);
	}
	if (env)
	{
		free(env->value);
		free(env);
	}
}


void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}