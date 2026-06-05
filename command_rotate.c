/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:32:31 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/05 14:55:18 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	rotate(t_node **stack)
{
	t_node	*last_node;
	int		length;

	length = get_stack_length(*stack);
	if (*stack == NULL || stack == NULL || length == 1)
		return ;
	last_node = get_last_node(*stack);
	last_node->node_after = *stack;
	*stack = (*stack)->node_after;
	(*stack)->node_before = NULL;
	last_node->node_after->node_before = last_node;
	last_node->node_after->node_after = NULL;
}

void	rotate_a(t_node **a)
{
	rotate(a);
	if (*a && (*a)->bench)
		(*a)->bench->ra++;
	write(1, "ra\n", 3);
}

void	rotate_b(t_node **b)
{
	rotate(b);
	if (*b && (*b)->bench)
		(*b)->bench->rb++;
	write(1, "rb\n", 3);
}

void	rotate_both(t_node **a, t_node **b)
{
	rotate(a);
	rotate(b);
	if (*a && (*a)->bench)
		(*a)->bench->rr++;
	write(1, "rr\n", 3);
}
