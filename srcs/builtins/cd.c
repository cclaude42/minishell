/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:46:37 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/16 17:28:48 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_error(char **args)
{
	ft_putstr_fd("cd: ", 2);
	if (args[2])
		ft_putstr_fd("string not in pwd: ", 2);
	else
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(args[1], 2);
}

static char		*get_env_path(t_env *env, const char *var, size_t len)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, var, len) == 0)
		{
			s_alloc = ft_strlen(env->value) - len;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > (int)len)
					oldpwd[j++] = env->value[i];
			}
			oldpwd[j] = '\0';
			return (oldpwd);
		}
		env = env->next;
	}
	return (NULL);
}

int				ft_cd(char **args, t_env *env)
{
	int		cd_ret;
	char	*env_path;

	env_path = NULL;
	if (!args[1])
	{
		env_path = get_env_path(env, "HOME", 4);
		cd_ret = chdir(env_path);
	}
	else
	{
		if (ft_strcmp(args[1], "-") == 0)
		{
			env_path = get_env_path(env, "OLDPWD", 6);
			cd_ret = chdir(env_path);
		}
		else
			cd_ret = chdir(args[1]);
	}
	if (cd_ret != 0)
		print_error(args);
	if (env_path)
		free(env_path);
	return (cd_ret);
}