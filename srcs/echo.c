/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 16:43:35 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 17:04:31 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			mini_echo(char **args)
{
	int		i;
	int		nl;

	nl = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
		nl = 0;
	i = 2 - nl;
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl == 1)
		write(1, "\n", 1);
	return (1);
}
