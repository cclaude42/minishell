/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:44:41 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/13 09:58:15 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_export(char **args, char **env)
{
	int		i;

	i = 0;
	while (env[i])
		i++;
	if (args[1] && ft_isin('=', args[1]))
	{
		env[i] = ft_strdup(args[1]);
		env[i + 1] = NULL;
	}
	return (1);
}
