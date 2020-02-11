/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 15:49:42 by cclaude           #+#    #+#             */
/*   Updated: 2019/10/18 14:47:44 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libutils.h"

static t_list	*map_free(t_list *start, void (*del)(void *))
{
	t_list	*temp;
	t_list	*next;

	temp = start;
	while (temp != NULL)
	{
		next = temp->next;
		del(temp->content);
		free(temp);
		temp = next;
	}
	return (NULL);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*temp;
	t_list	*prev;
	t_list	*start;

	temp = lst;
	start = NULL;
	prev = NULL;
	while (temp != NULL && f != NULL && del != NULL)
	{
		if (!(lstnew = malloc(sizeof(t_list))))
			return (map_free(start, del));
		lstnew->content = f(temp->content);
		if (prev != NULL)
			prev->next = lstnew;
		prev = lstnew;
		temp = temp->next;
		if (start == NULL)
			start = lstnew;
	}
	if (lst != NULL && f != NULL && del != NULL)
		lstnew->next = NULL;
	return (start);
}
