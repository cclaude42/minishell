/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/08 19:46:37 by macrespo          #+#    #+#             */
/*   Updated: 2020/06/12 20:11:46 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_cd(char **args, t_env *env)
{
	char	*error_msg;
	int		cd_ret;

	(void)env;
	cd_ret = chdir(args[1]);
	if (cd_ret != 0)
	{
		if (args[2])
			error_msg = ft_strjoin("cd: string not in pwd: ", args[1]);
		else
		{
			error_msg = ft_strjoin("cd: ", strerror(errno));
			error_msg = ft_strjoin(error_msg, ": ");
			error_msg = ft_strjoin(error_msg, args[1]);
		}
		ft_putendl_fd(error_msg, 2);
		free(error_msg);
		return (cd_ret);
	}
	else
		return (0);
}