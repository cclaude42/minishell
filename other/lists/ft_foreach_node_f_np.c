/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_foreach_node_f_np.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 12:57:26 by ssingevi          #+#    #+#             */
/*   Updated: 2020/01/23 16:36:34 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_linked.h"

void		ft_foreach_node_f_np(t_pnp **begin_list, int (*f)(t_pnp *curr))
{
	t_pnp	*tmp;
	t_pnp	*tmp2;

	tmp = *begin_list;
	while (tmp->next)
	{
		tmp2 = tmp->next;
		f(tmp);
		tmp = tmp2;
	}
}
