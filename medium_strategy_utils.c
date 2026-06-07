/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_strategy_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-07 21:42:32 by roaleksa          #+#    #+#             */
/*   Updated: 2026-06-07 21:42:32 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	Searches from the bottom of the stack upward.
	Returns distance to the first node in [min,max],
	or -1 if no matching node exists.
*/
static int	distance_from_bottom(t_node *stack, int min, int max)
{
	int		distance;
	t_node	*bottom;

	if (!stack)
		return (-1);
	bottom = stack;
	while (bottom->node_after)
		bottom = bottom->node_after;
	distance = 0;
	while (bottom)
	{
		if (bottom->index >= min && bottom->index <= max)
			return (distance);
		distance++;
		bottom = bottom->node_before;
	}
	return (-1);
}

/*
	Searches from the top of the stack downward.
	Returns distance to the first node in [min,max],
	or -1 if none found.
*/
static int	distance_from_top(t_node *stack, int min, int max)
{
	int	distance;

	distance = 0;
	while (stack)
	{
		if (stack->index >= min && stack->index <= max)
			return (distance);
		distance++;
		stack = stack->node_after;
	}
	return (-1);
}

/*
	Chooses the closest chunk node in A from top or bottom.
	Returns positive top distance or negative bottom distance.
*/
static int	find_nearest_chunk_value(t_node *a, int min, int max)
{
	int	top_dist;
	int	bottom_dist;

	top_dist = distance_from_top(a, min, max);
	bottom_dist = distance_from_bottom(a, min, max);
	if (top_dist <= bottom_dist)
		return (top_dist);
	return (-(bottom_dist + 1));
}

/*
	Checks whether stack contains any node
	index in chunk range. Used to know when
	the current chunk has been fully moved.
*/
static bool	contains_chunk_value(t_node *stack, int min, int max)
{
	while (stack)
	{
		if (stack->index >= min && stack->index <= max)
			return (true);
		stack = stack->node_after;
	}
	return (false);
}

/*
	Used in the Medium sorting strategy.
	Moves all nodes in the current chunk
	from A to B. Rotates B for smaller values
	to keep larger chunk values near top.
*/
void	push_chunk(t_node **a, t_node **b, int min, int max)
{
	int	pos;
	int	middle;

	middle = (min + max) / 2;
	while (contains_chunk_value(*a, min, max))
	{
		pos = find_nearest_chunk_value(*a, min, max);
		move_to_top_a(a, pos);
		push_to_b(a, b);
		if ((*b)->index < middle)
			rotate_b(b);
	}
}
