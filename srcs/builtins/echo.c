/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 17:15:26 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/08 18:04:45 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_echo(char **args, int n_option)
{
	int		i;

	i = 1;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (n_option == 1)
		write(1, "\n", 1);
	return (0);
}