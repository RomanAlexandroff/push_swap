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

static void	move_to_top_b(t_node **b, int pos) 			// potentially can be replaced with ensure_top() from sort_many_nodes.c
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

static void	push_back_sorted(t_node **a, t_node **b)
{
	int	pos;

	while (*b)
	{
		pos = find_max_position(*b);					// DONE here in the file
		move_to_top_b(b, pos);					// DONE here in the file
		push_to_a(a, b);							// ORIGINAL from command_push.c
	}
}

static void	move_to_top_a(t_node **a, int pos) 			// potentially can be replaced with ensure_top() from sort_many_nodes.c
{
	if (pos >= 0)
	{
		while (pos--)
			rotate_a(a);							// ORIGINAL from command_rotate.c
	}
	else
	{
		pos = -pos;
		while (pos--)
			reverse_a(a);							// ORIGINAL from command_reverse.c
	}
}

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

static int	find_nearest_chunk_value(t_node *a, int min, int max)
{
	int	top_dist;
	int	bottom_dist;

	top_dist = distance_from_top(a, min, max);						// DONE here in the file
	bottom_dist = distance_from_bottom(a, min, max);					// DONE here in the file

	if (top_dist <= bottom_dist)
		return (top_dist);
	return (-(bottom_dist));
}

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

static void	push_chunk(t_node **a, t_node **b, int min, int max)
{
	int	pos;
	int	middle;

	middle = (min + max) / 2;
	while (contains_chunk_value(*a, min, max))					// DONE here in the file
	{
		pos = find_nearest_chunk_value(*a, min, max);				// DONE here in the file
		move_to_top_a(a, pos);									// DONE here in the file
		push_to_b(a, b);									// ORIGINAL from command_push.c
		if ((*b)->index < middle)
			rotate_b(b);									// ORIGINAL from command_rotate.c
	}
}

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

void	medium_sort(t_node **a, t_node **b)
{
	int	size;
	int	chunk_count;
	int	chunk_size;
	int	chunk;
	int	start;
	int	end;

	assign_sorting_rank(*a);								// DONE here in the file
	size = get_stack_length(*a);							// ORIGINAL from stack_calculations.c
	chunk_count = ft_sqrt(size);					// DONE here in the file
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
		push_chunk(a, b, start, end);					// DONE here in the file
		chunk++;
	}
	push_back_sorted(a, b);								// DONE here in the file
}
