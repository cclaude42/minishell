/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macrespo <macrespo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 16:04:10 by macrespo          #+#    #+#             */
/*   Updated: 2020/08/11 16:04:37 by macrespo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_printf("\b\b  ");
		ft_printf("\n");
		ft_printf("\033[0;36mminishell > \033[0m");
		g_sig.exit_status = 1;
	}
	else
	{
		ft_printf("\n");
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	if (g_sig.pid != 0)
	{
		ft_printf("Quit: %d\n", code);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_printf("\b\b  \b\b");
}

void	sig_init(void)
{
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
	g_sig.pid = 0;
	g_sig.exit_status = 0;
}
