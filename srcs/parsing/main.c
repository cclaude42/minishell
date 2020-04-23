/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 13:53:51 by cclaude           #+#    #+#             */
/*   Updated: 2020/04/21 13:55:51 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int ac, char **av)
{
	t_token	*list;
	int		i;

	(void)ac;
	i = 0;
	list = get_args(av[1]);
	if (!list)
		return (0);
	while (list->next)
	{
		printf("#%d %s %d\n", i, list->tok, list->type);
		free(list->tok);
		list = list->next;
		free(list->prev);
		i++;
	}
	printf("#%d %s %d\n", i, list->tok, list->type);
	free(list->tok);
	free(list);
	return (0);
}
