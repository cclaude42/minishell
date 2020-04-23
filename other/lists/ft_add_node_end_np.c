/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_end_np.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:28:23 by ssingevi          #+#    #+#             */
/*   Updated: 2020/01/23 11:13:28 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		ft_add_node_end_np(t_pnp **begin_list, t_pnp *new)
{
	t_pnp	*tmp;

	if (!(*begin_list))
		*begin_list = new;
	else
	{
		tmp = *begin_list;
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
		new->next = NULL;
	}
	(*begin_list)->prev = new;
}
