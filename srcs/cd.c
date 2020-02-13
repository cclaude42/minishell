/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:44:08 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 18:43:09 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_cd(char **args, char **env)
{
	char	*path;
	char	cwd[PATH_MAX];

	(void)env;
	getcwd(cwd, sizeof(cwd));
	if (!args[1])
	{
		path = get_env(env, "HOME=");
		if ((chdir(path)) != 0)
			write(2, "cd: no such file or directory\n", 30);
	}
	else if (args[1] && !args[2])
	{
		if ((chdir(args[1])) != 0)
			write(2, "cd: no such file or directory\n", 30);
	}
	else
		write(2, "cd: too many arguments\n", 23);
	return (1);
}
