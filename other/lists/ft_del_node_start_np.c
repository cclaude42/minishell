/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_node_start_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:20:53 by ssingevi          #+#    #+#             */
/*   Updated: 2019/11/29 15:50:30 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <rt.h>

void		ft_del_node_start_np(t_pnp **begin_list, void (*f)(t_pnp *curr))
{
	t_pnp	*tmp;

	tmp = *begin_list;
	*begin_list = (*begin_list)->next;
	(*begin_list)->next->prev = NULL;
	if (f)
		f(tmp);
	try_free_((void **)&tmp, NULL, 0);
}
