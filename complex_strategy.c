/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex_strategy.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:00:07 by ccrucian          #+#    #+#             */
/*   Updated: 2026/06/05 13:16:43 by ccrucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 *Assigns an index from 0 to length - 1 to each node based
 * on the relative order of its value, in order to compress
 * the values in an easier way to process them.
 */
static void	assign_index(t_node *stack)
{
	t_node	*current;
	t_node	*i_node;

	current = stack;
	while (current)
	{
		current->index = 0;
		i_node = stack;
		while (i_node)
		{
			if (current->value > i_node->value)
				current->index++;
			i_node = i_node->node_after;
		}
		current = current->node_after;
	}
}

/*
 * Calculate the maximum number of bits needed to represent 
 * the biggest index in the stack. 
*/
static int	get_max_bits(t_node *a)
{
	int	max_bits;
	int	max_index;

	max_index = 0;
	while (a)
	{
		if (a->index > max_index)
			max_index = a->index;
		a = a->node_after;
	}
	max_bits = 0;
	while (max_index > 0)
	{
		max_index = max_index / 2;
		max_bits++;
	}
	return (max_bits);
}

/*
 * Sorts the stack using a binary radix sort algorithm.
 * Each node is indexed according to its relative order,
 * then elements are sorted bit by bit using two stacks.
 */
void	complex_strategy(t_node **a, t_node **b)
{
	int	length;
	int	max_bits;
	int	i;
	int	bit_read;

	length = get_stack_length(*a);
	assign_index(*a);
	max_bits = get_max_bits(*a);
	bit_read = 0;
	while (bit_read < max_bits)
	{
		i = length;
		while (i--)
		{
			if (((*a)->index >> bit_read) & 1)
				rotate_a(a);
			else
				push_to_b(a, b);
		}
		while (*b)
			push_to_a(a, b);
		bit_read++;
	}
}
