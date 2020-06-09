/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:33:30 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/09 15:41:31 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_builtin(char	*command)
{
	if (ft_strcmp(command, "echo") == 0)
		return (1);
	else if (ft_strcmp(command, "cd") == 0)
		return (1);
	else if (ft_strcmp(command, "pwd") == 0)
		return (1);
	else if (ft_strcmp(command, "env") == 0)
		return (1);
	else
		return (0);
}

int		exec_builtins(char **args, char **env)
{
	int		result;

	(void)env;
	result = 0;
	if (ft_strcmp(args[0], "echo") == 0)
		result = ft_echo(args);
	else if (ft_strcmp(args[0], "cd") == 0)
		result = ft_cd(args, env);
	else if (ft_strcmp(args[0], "pwd") == 0)
		result = ft_pwd();
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(env);
	return result;	
}