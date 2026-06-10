/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:42:08 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 14:09:45 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Next node to solve is the node from stack B with
 * the least amount of steps to sort into stack A
*/
static t_node	*find_next_to_solve(t_node *stack)
{
	if (stack == NULL)
		return (NULL);
	while (stack)
	{
		if (stack->next_to_solve)
			return (stack);
		stack = stack->node_after;
	}
	return (NULL);
}

static void	ensure_top(t_node **stack, t_node *node, char name)
{
	while (*stack != node)
	{
		if (name == 'a')
		{
			if (node->top_half_flag)
				rotate_a(stack);
			else
				reverse_a(stack);
		}
		else if (name == 'b')
		{
			if (node->top_half_flag)
				rotate_b(stack);
			else
				reverse_b(stack);
		}	
	}
}

static void	solve_node(t_node **a, t_node **b)
{
	t_node	*node;

	node = find_next_to_solve(*b);
	if (node->top_half_flag && node->destination->top_half_flag)
    {
	    while (*a != node->destination && *b != node)
		    rotate_both(a, b);
	    position_update(*a);
	    position_update(*b);
    }
	else if (!(node->top_half_flag) && !(node->destination->top_half_flag))
    {
	    while (*a != node->destination && *b != node)
		    reverse_both(a, b);
	    position_update(*a);
	    position_update(*b);
    }
	ensure_top(b, node, 'b');
	ensure_top(a, node->destination, 'a');
	push_to_a(a, b);
}

void	sort_five(t_node **a, t_node **b)
{
    t_node	*smallest_node;

	while (get_stack_length(*a) > 3)
	{
		update_nodes(*a, *b);
		ensure_top(a, get_lowest_value(*a), 'a');
		push_to_b(a, b);
	}
	sort_three(a);
	while (*b)
	{
		update_nodes(*a, *b);
		solve_node(a, b);
	}
	position_update(*a);
	smallest_node = get_lowest_value(*a);
	if (smallest_node->top_half_flag)
		while (*a != smallest_node)
			rotate_a(a);
	else
		while (*a != smallest_node)
			reverse_a(a);
}