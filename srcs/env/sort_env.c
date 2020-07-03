/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/03 15:03:17 by macrespo          #+#    #+#             */
/*   Updated: 2020/07/03 15:18:06 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void     print_debug(t_env *env)
{
    printf("DEBUG ENV\n");
    while (env)
    {
        printf("%s\n", env->value);
        env = env->next;
    }
}

t_env   *env_cpy(t_env *env)
{
    t_env   *sorted_env;
    t_env   *new_elt;
    t_env   *first_link;

    if (!(sorted_env = malloc(sizeof(t_env*))))
		return (NULL);
	sorted_env->value = ft_strdup(env->value);
	sorted_env->next = NULL;
    first_link = sorted_env;
    env = env->next;
    while (env)
    {
        if (!(new_elt = malloc(sizeof(t_env*))))
		    return (NULL);
        new_elt->value = ft_strdup(env->value);
        new_elt->next = NULL;
        sorted_env->next = new_elt;
        sorted_env = new_elt;
        env = env->next;
    }
    print_debug(first_link);
    return (first_link);
}