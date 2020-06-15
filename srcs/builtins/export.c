/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 18:15:54 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/15 19:54:52 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char **args, t_env **env)
{
	t_env	*new;
	// t_env	*tmp;

	if (!(new  = malloc(sizeof(t_env *))))
		return (1);
	new->value = args[1];
	new->next = *env;
	*env = new;
	// ft_env(*env);
	return (0);
}