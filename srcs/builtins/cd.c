/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:46:37 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/15 17:46:54 by macrespo         ###   ########.fr       */
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

static char		*get_oldpwd(t_env *env)
{
	char	*oldpwd;
	int		i;
	int		j;
	int		s_alloc;

	while (env && env->next != NULL)
	{
		if (ft_strncmp(env->value, "OLDPWD", 6) == 0)
		{
			s_alloc = ft_strlen(env->value - 7) + 1;
			if (!(oldpwd = malloc(sizeof(char) * s_alloc)))
				return (NULL);
			i = 0;
			j = 0;
			while (env->value[i++])
			{
				if (i > 6)
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
	char	*oldpwd;

	if (ft_strcmp(args[1], "-") == 0)
	{
		oldpwd = get_oldpwd(env);
		cd_ret = chdir(oldpwd);
		free(oldpwd);
	}
	else
		cd_ret = chdir(args[1]);
	if (cd_ret != 0)
	{
		print_error(args);
		return (1);
	}
	else
		return (0);
}