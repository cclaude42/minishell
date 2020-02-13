/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:45:09 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 21:15:28 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_unset(char **args, char **env)
{
	int		i;
	int		len;
	int		found;

	i = 0;
	found = 0;
	len = ft_strlen(args[1]);
	while (env[i] && args[1])
	{
		if (ft_strncmp(env[i], args[1], len) == 0 && env[i][len] == '=')
			found = 1;
		if (found)
			env[i] = env[i + 1];
		i++;
	}
	return (1);
}
