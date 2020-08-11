/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:01:42 by macrespo          #+#    #+#             */
/*   Updated: 2020/08/11 16:03:58 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			increment_shell_level(t_env *env)
{
	int		shell_level;
	char	env_name[BUFF_SIZE];
	char	*shlvl;

	shell_level = ft_atoi(get_env_value("SHLVL", env)) + 1;
	while (env && env->next)
	{
		get_env_name(env_name, env->value);
		if (ft_strcmp("SHLVL", env_name) == 0)
		{
			ft_memdel(env->value);
			shlvl = ft_itoa(shell_level);
			env->value = ft_strjoin("SHLVL=", shlvl);
			ft_memdel(shlvl);
			return ;
		}
		env = env->next;
	}
}

size_t			size_env(t_env *lst)
{
	size_t	lst_len;

	lst_len = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			lst_len += ft_strlen(lst->value);
			lst_len++;
		}
		lst = lst->next;
	}
	return (lst_len);
}

char			*env_to_str(t_env *lst)
{
	char	*env;
	int		i;
	int		j;

	if (!(env = malloc(sizeof(char) * size_env(lst) + 1)))
		return (NULL);
	i = 0;
	while (lst && lst->next != NULL)
	{
		if (lst->value != NULL)
		{
			j = 0;
			while (lst->value[j])
			{
				env[i] = lst->value[j];
				i++;
				j++;
			}
		}
		if (lst->next->next != NULL)
			env[i++] = '\n';
		lst = lst->next;
	}
	env[i] = '\0';
	return (env);
}

int				env_init(t_mini *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	if (!(env = malloc(sizeof(t_env*))))
		return (1);
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1;
	while (env_array[i])
	{
		if (!(new = malloc(sizeof(t_env*))))
			return (1);
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		env->next = new;
		env = new;
		i++;
	}
	return (0);
}
