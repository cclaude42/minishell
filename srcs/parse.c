/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:58:38 by cclaude           #+#    #+#             */
/*   Updated: 2020/02/12 16:49:22 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_args(char **args)
{
	int		i;

	i = 0;
	while (args[i])
		ft_memdel(args[i++]);
	ft_memdel(args);
}

char	**command_parse(char *command)
{
	return (ft_split(command, ' '));
}
