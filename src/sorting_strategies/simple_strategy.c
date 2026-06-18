/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_strategy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 17:17:44 by ccrucian          #+#    #+#             */
/*   Updated: 2026/06/10 15:40:51 by ccrucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

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

/*
	Sorts the stack by repeatedly moving the smallest node
	from stack A to stack B using the shortest rotation path.
	Once all nodes are moved, elements are pushed back to A
	in sorted order. 
	It is a Selection Sort alghorithm adapted for two stacks.
*/
void	simple_strategy(t_node **a, t_node **b)
{
	t_node	*smallest_node;

	set_benchmark(a, "Simple", "O(n2)", SKIP_DISORDER);
	if (small_sort(a, b, get_stack_length(*a)))
		return ;
	while (*a)
	{
		smallest_node = get_lowest_value(*a);
		position_update(*a);
		while (*a != smallest_node)
		{
			if (smallest_node->top_half_flag)
				rotate_a(a);
			else
				reverse_a(a);
		}
		push_to_b(a, b);
	}
	while (*b)
		push_to_a(a, b);
}
