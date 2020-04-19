/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_linked.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssingevi <ssingevi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:19:17 by ssingevi          #+#    #+#             */
/*   Updated: 2020/01/27 13:26:34 by ssingevi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOUBLE_LINKED_H
# define DOUBLE_LINKED_H

# include <stdlib.h>
# include <stdarg.h>
# include <rt.h>
# define SUCCESS 0
# define FAILURE 1

typedef struct						s_pattern_list_np
{
	struct s_pattern_list_np		*next;
	struct s_pattern_list_np		*prev;
}									t_pattern_list_np;
typedef struct s_pattern_list_np	t_pnp;
void								ft_del_list_np(t_pnp **begin_list);
void								*ft_new_node(
										size_t size, void (*f)(void *, int,
										va_list), int nb_arg, ...);
void								ft_add_node_end_np(t_pnp **begin_list,
	t_pnp *new);
void								ft_add_node_f_nextto_np(
	t_pnp **begin_list, t_pnp *new, int(*f)(t_pnp *curr));
void								ft_add_node_f_prevto_np(
	t_pnp **begin_list, t_pnp *new, int(*f)(t_pnp *curr));
void								ft_add_node_nextto_np(t_pnp *prev,
	t_pnp *new);
void								ft_add_node_prevto_np(t_pnp **start,
	t_pnp *next, t_pnp *new);
void								ft_add_node_start_np(t_pnp **begin_list,
	t_pnp *new);
void								ft_del_node_end_np(t_pnp **begin_list,
	void (*f)(t_pnp *curr));
void								ft_del_node_np(t_pnp **begin_list,
	t_pnp *del, void (*f)(t_pnp *curr));
void								ft_del_node_start_np(t_pnp **begin_list,
	void (*f)(t_pnp *curr));
void								ft_foreach_node_f_np(t_pnp **begin_list,
	int(*f)(t_pnp *curr));
void								ft_swap_node_np(t_pnp **begin_list,
	t_pnp *node_a, t_pnp *node_b);
#endif
