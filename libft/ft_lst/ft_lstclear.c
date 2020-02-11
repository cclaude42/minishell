/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:49:04 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/16 16:17:50 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*current;
	t_list	*prev;

	if (*lst == NULL || !(current = *lst) || !del)
		return ;
	while (current->next != NULL)
	{
		prev = current;
		del(current->content);
		free(current);
		current = prev->next;
	}
	del(current->content);
	free(current);
	*lst = NULL;
}
