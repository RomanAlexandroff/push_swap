/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_push.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:32:17 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:32:17 by roaleksa         ###   ########.fr       */
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
	write(1, "pa\n", 3);
}

void	push_to_b(t_node **a, t_node **b)
{
	push(a, b);
	write(1, "pb\n", 3);
}
