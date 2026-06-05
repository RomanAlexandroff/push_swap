/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:32:23 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/05 14:54:44 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse(t_node **stack)
{
	t_node	*last_node;
	int		length;

	length = get_stack_length(*stack);
	if (*stack == NULL || stack == NULL || length == 1)
		return ;
	last_node = get_last_node(*stack);
	last_node->node_before->node_after = NULL;
	last_node->node_after = *stack;
	last_node->node_before = NULL;
	*stack = last_node;
	last_node->node_after->node_before = last_node;
}

void	reverse_a(t_node **a)
{
	reverse(a);
	if (*a && (*a)->bench)
		(*a)->bench->rra++;
	write(1, "rra\n", 4);
}

void	reverse_b(t_node **b)
{
	reverse(b);
	if (*b && (*b)->bench)
		(*b)->bench->rrb++;
	write(1, "rrb\n", 4);
}

void	reverse_both(t_node **a, t_node **b)
{
	reverse(a);
	reverse(b);
	if (*a && (*a)->bench)
		(*a)->bench->rrr++;
	write(1, "rrr\n", 4);
}
