/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:33:26 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:33:26 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*get_last_node(t_node *node)
{
	if (node == NULL)
		return (NULL);
	while (node->node_after)
		node = node->node_after;
	return (node);
}

t_node	*get_lowest_value(t_node *stack)
{
	long	lowest_value;
	t_node	*smallest_node;

	if (stack == NULL)
		return (NULL);
	lowest_value = LONG_MAX;
	while (stack)
	{
		if (stack->value < lowest_value)
		{
			lowest_value = stack->value;
			smallest_node = stack;
		}
		stack = stack->node_after;
	}
	return (smallest_node);
}

/*
 * Next node to solve is the node from stack B with
 * the least amount of steps to sort into stack A
*/
t_node	*find_next_to_solve(t_node *stack)
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

int	get_stack_length(t_node *stack)
{
	int	count;

	count = 0;
	if (stack == NULL)
		return (count);
	while (stack)
	{
		count++;
		stack = stack->node_after;
	}
	return (count);
}

bool	is_sorted(t_node *stack)
{
	if (stack == NULL)
		return (true);
	while (stack->node_after)
	{
		if (stack->value > stack->node_after->value)
			return (false);
		stack = stack->node_after;
	}
	return (true);
}
