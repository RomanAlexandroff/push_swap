/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-01 10:26:04 by roaleksa          #+#    #+#             */
/*   Updated: 2026-06-01 10:26:04 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/* 
	Moves the node at position pos in stack B to the top.
	Uses rotate or reverse depending on which path is shorter.
*/
static void	move_to_top_b(t_node **b, int pos)
{
	int	size;

	size = get_stack_length(*b);
	if (pos <= size / 2)
	{
		while (pos > 0)
		{
			rotate_b(b);
			pos--;
		}
	}
	else
	{
		pos = size - pos;
		while (pos > 0)
		{
			reverse_b(b);
			pos--;
		}
	}
}

/*
	Scans stack B to find the node with the largest index.
	Returns that node’s position from the top.
*/
static int	find_max_position(t_node *stack)
{
	int	max_index;
	int	max_position;
	int	position;

	max_index = stack->index;
	max_position = 0;
	position = 0;
	while (stack)
	{
		if (stack->index > max_index)
		{
			max_index = stack->index;
			max_position = position;
		}
		position++;
		stack = stack->node_after;
	}
	return (max_position);
}

/*
	Repeatedly moves the largest node from B back to A.
	Ensures B is emptied in descending index order.
*/
static void	push_back_sorted(t_node **a, t_node **b)
{
	int	pos;

	while (*b)
	{
		pos = find_max_position(*b);
		move_to_top_b(b, pos);
		push_to_a(a, b);
	}
}

/*
	Rotates or reverse-rotates stack A to bring a node to top.
	pos is positive for rotations and negative for reverse.
*/
static void	move_to_top_a(t_node **a, int pos)
{
	if (pos >= 0)
	{
		while (pos--)
			rotate_a(a);
	}
	else
	{
		pos = -pos;
		while (pos--)
			reverse_a(a);
	}
}

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
	Moves all nodes in the current chunk
	from A to B. Rotates B for smaller values
	to keep larger chunk values near top.
*/
static void	push_chunk(t_node **a, t_node **b, int min, int max)
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

/*
	Assigns each node an index rank based
	on value order. Smaller values get
	smaller indices for sorting decisions.
*/
static void	assign_sorting_rank(t_node *stack)
{
	t_node	*current;
	t_node	*compare;
	int		count;

	current = stack;
	while (current)
	{
		count = 0;
		compare = stack;
		while (compare)
		{
			if (compare->value < current->value)
				count++;
			compare = compare->node_after;
		}
		current->index = count;
		current = current->node_after;
	}
}

/*
	Computes integer square root of nb.
	Used to determine the number of chunks.
*/
static int	ft_sqrt(int nb)
{
	int	low;
	int	high;
	int	mid;
	int	ans;

	if (nb <= 0)
		return (0);
	low = 1;
	high = nb;
	ans = 1;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if ((long)mid * mid <= nb)
		{
			ans = mid;
			low = mid + 1;
		}
		else
			high = mid - 1;
	}
	return (ans);
}

/*
	Medium sort using sqrt(n) chunks.
	Ranks A, divides into chunks, pushes
	chunks to B, then rebuilds A
*/
void	medium_strategy(t_node **a, t_node **b)
{
	int	size;
	int	chunk_count;
	int	chunk_size;
	int	chunk;
	int	start;
	int	end;

	set_benchmark(a, "Medium", "O(n√n)", SKIP_DISORDER);
	assign_sorting_rank(*a);
	size = get_stack_length(*a);
	chunk_count = ft_sqrt(size);
	if (chunk_count == 0)
		chunk_count = 1;
	chunk_size = size / chunk_count;
	chunk = 0;
	while (chunk < chunk_count)
	{
		start = chunk * chunk_size;
		end = start + chunk_size - 1;
		if (chunk == chunk_count - 1)
			end = size - 1;
		push_chunk(a, b, start, end);
		chunk++;
	}
	push_back_sorted(a, b);
}
