/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:32:17 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/05 14:46:39 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_node **from, t_node **to)
{
	t_node	*node_to_push;

	if (*from == NULL)
		return ;
	node_to_push = *from;
	*from = (*from)->node_after;
	if (*from)
		(*from)->node_before = NULL;
	node_to_push->node_before = NULL;
	if (*to == NULL)
	{
		*to = node_to_push;
		node_to_push->node_after = NULL;
	}
	else
	{
		node_to_push->node_after = *to;
		node_to_push->node_after->node_before = node_to_push;
		*to = node_to_push;
	}
}

void	push_to_a(t_node **a, t_node **b)
{
	push(b, a);
	if (*a && (*a)->bench)
		(*a)->bench->pa++;
	write(FD_STDOUT, "pa\n", 3);
}

void	push_to_b(t_node **a, t_node **b)
{
	push(a, b);
	if (*b && (*b)->bench)
		(*b)->bench->pb++;
	write(FD_STDOUT, "pb\n", 3);
}
