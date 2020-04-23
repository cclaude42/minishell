/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/29 14:33:35 by ssingevi          #+#    #+#             */
/*   Updated: 2020/01/09 15:02:13 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		ft_del_node_np(t_pnp **begin_list, t_pnp *del,
	void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	if (tmp == del)
	{
		*begin_list = (*begin_list)->next;
		if (*begin_list)
			(*begin_list)->prev = NULL;
	}
	else
	{
		while (tmp->next != del)
			tmp = tmp->next;
		if (tmp->next == NULL)
			return ;
		tmp->next = del->next;
		tmp->next->prev = tmp;
	}
	if (f)
		f(del);
	try_free_((void **)&del, NULL, 0);
}
