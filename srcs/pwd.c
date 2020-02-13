/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:44:29 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 18:29:36 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_pwd(char **args, char **env)
{
	char	cwd[PATH_MAX];

	(void)args;
	(void)env;
	getcwd(cwd, sizeof(cwd));
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (1);
}
