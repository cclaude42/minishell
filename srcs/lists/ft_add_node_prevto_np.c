/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_node_prevto_np.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 14:42:34 by ssingevi          #+#    #+#             */
/*   Updated: 2019/11/17 14:56:25 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_linked.h"

void		ft_add_node_prevto_np(t_pnp **start, t_pnp *next, t_pnp *new)
{
	if (!new && !next && !(*start))
		return ;
	if (*start == next)
		ft_add_node_start_np(start, new);
	else
	{
		new->next = next;
		new->prev = next->prev;
		next->prev->next = new;
		next->prev = new;
	}
}
