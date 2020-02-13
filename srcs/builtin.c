/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:08:09 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 17:05:48 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_builtin(char **args, char **env)
{
	int		ret;

	ret = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		ret = mini_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		ret = mini_cd(args, env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ret = mini_pwd(args, env);
	else if (ft_strcmp(args[0], "export") == 0)
		ret = mini_export(args, env);
	else if (ft_strcmp(args[0], "unset") == 0)
		ret = mini_unset(args, env);
	else if (ft_strcmp(args[0], "env") == 0)
		ret = mini_env(args, env);
	return (ret);
}
