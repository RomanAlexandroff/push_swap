/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   medium_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 10:26:04 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 15:41:07 by ccrucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	Used in the Medium sorting strategy.
	Rotates or reverse-rotates stack A
	to bring a node to top. pos is positive
	for rotations and negative for reverse.
*/
void	move_to_top_a(t_node **a, int pos)
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
	Used in the Medium sorting strategy.
	Moves the node at position pos in stack
	B to the top. Uses rotate or reverse
	depending on which path is shorter.
*/
void	move_to_top_b(t_node **b, int pos)
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
	Used in the Medium sorting strategy.
	Repeatedly moves the largest node
	from B back to A. Ensures B is emptied
	in descending index order.
*/
static void	push_back_sorted(t_node **a, t_node **b)
{
	int		max_index;
	int		max_position;
	int		position;
	t_node	*current;

	while (*b)
	{
		max_index = (*b)->index;
		max_position = 0;
		position = 0;
		current = *b;
		while (current)
		{
			if (current->index > max_index)
			{
				max_index = current->index;
				max_position = position;
			}
			position++;
			current = current->node_after;
		}
		move_to_top_b(b, max_position);
		push_to_a(a, b);
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
	Medium sort using sqrt(n) chunks.
	Ranks A, divides into chunks, pushes
	chunks to B, then rebuilds A.
	Chunk-based Sort algorithm for 2 stacks
*/
void	medium_strategy(t_node **a, t_node **b, int size)
{
	int	chunk_count;
	int	chunk_size;
	int	chunk;
	int	start;
	int	end;

	set_benchmark(a, "Medium", "O(n√n)", SKIP_DISORDER);
	if (small_sort(a, b, get_stack_length(*a)))
		return ;
	assign_sorting_rank(*a);
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
