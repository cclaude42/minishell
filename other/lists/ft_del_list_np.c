/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del_list_np.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:36:42 by ssingevi          #+#    #+#             */
/*   Updated: 2020/01/23 16:44:15 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "double_linked.h"

void		ft_del_list_np(t_pnp **begin_list)
{
	t_pnp	*tmp;
	t_pnp	*tmp2;

	tmp = *begin_list;
	while (tmp)
	{
		tmp2 = tmp->next;
		try_free_((void **)&tmp, NULL, 0);
		tmp = tmp2;
	}
}
