/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:33:29 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:33:29 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Destination for stack B node is
 * above stack A node with bigger value
*/
static void	destination_update(t_node *a, t_node *b)
{
	t_node	*current_a;
	t_node	*destination;
	long	best_match_index;

	best_match_index = LONG_MAX;
	while (b)
	{
		current_a = a;
		while (current_a)
		{
			if (current_a->value > b->value
				&& current_a->value < best_match_index)
			{
				best_match_index = current_a->value;
				destination = current_a;
			}
			current_a = current_a->node_after;
		}
		if (best_match_index == LONG_MAX)
			b->destination = get_lowest_value(a);
		else
			b->destination = destination;
		b = b->node_after;
	}
}

void	position_update(t_node *stack)
{
	int	i;
	int	centerline;

	i = 0;
    centerline = 0;
	if (stack == NULL)
		return ;
	centerline = get_stack_length(stack) / 2;
	while (stack)
	{
		stack->node_position = i;
		if (i <= centerline)
			stack->top_half_flag = true;
		else
			stack->top_half_flag = false;
		stack = stack->node_after;
		++i;
	}
}

void	solving_cost_update(t_node *a, t_node *b)
{
	int	length_a;
	int	length_b;

	length_a = get_stack_length(a);
	length_b = get_stack_length(b);
	while (b)
	{
		b->solving_cost = b->node_position;
		if (!(b->top_half_flag))
			b->solving_cost = length_b - (b->node_position);
		if (b->destination->top_half_flag)
			b->solving_cost += b->destination->node_position;
		else
			b->solving_cost += length_a - (b->destination->node_position);
		b = b->node_after;
	}
}

/*
 * Next node to solve is the node from stack B with
 * the least amount of steps to sort into stack A
*/
void	next_to_solve_update(t_node *b)
{
	long	best_match_value;
	t_node	*best_match_node;

	if (b == NULL)
		return ;
	best_match_value = LONG_MAX;
	while (b)
	{
		if (b->solving_cost < best_match_value)
		{
			best_match_value = b->solving_cost;
			best_match_node = b;
		}
		b = b->node_after;
	}
	best_match_node->next_to_solve = true;
}

void	update_nodes(t_node *a, t_node *b)
{
    position_update(a);
	position_update(b);
	destination_update(a, b);
	solving_cost_update(a, b);
	next_to_solve_update(b);
}
