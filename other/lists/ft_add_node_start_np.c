/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_start_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 16:03:52 by ssingevi          #+#    #+#             */
/*   Updated: 2019/11/17 21:43:50 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_linked.h"

void		ft_add_node_start_np(t_pnp **begin_list, t_pnp *new)
{
	new->next = *begin_list;
	new->prev = NULL;
	if (*begin_list)
		(*begin_list)->prev = new;
	*begin_list = new;
}
