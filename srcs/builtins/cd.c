/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:46:37 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/08 20:07:30 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **args, char **env)
{
	char	*error_msg;

	(void)env;
	if (chdir(args[1]) != 0)
	{
		error_msg = ft_strjoin(strerror(errno), ": ");
		error_msg = ft_strjoin(error_msg, args[1]);
		ft_putendl_fd(error_msg, 2);
		free(error_msg);
		return (1);
	}
	else
		return (0);
}