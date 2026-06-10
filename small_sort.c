/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:42:21 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 16:12:06 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * Finds node with the largest value
*/
static t_node	*get_largest_node(t_node *stack)
{
	int		largest_value;
	t_node	*largest_node;

	largest_value = INT_MIN;
	if (stack == NULL)
		return (NULL);
	while (stack)
	{
		if (stack->value > largest_value)
		{
			largest_value = stack->value;
			largest_node = stack;
		}
		stack = stack->node_after;
	}
	return (largest_node);
}

void	sort_three(t_node **a)
{
	t_node	*largest_node;

	largest_node = get_largest_node(*a);
	if (*a == largest_node)
		rotate_a(a);
	else if ((*a)->node_after == largest_node)
		reverse_a(a);
	if ((*a)->value > (*a)->node_after->value)
		swap_a(a);
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

void	sort_five(t_node **a, t_node **b)
{
	t_node	*smallest_node;
	int		i;

	i = 0;
	while (i++ != 2)
	{
		smallest_node = get_lowest_value(*a);
		position_update(*a);
		ensure_top(a, smallest_node, 'a');
		push_to_b(a, b);
	}
	sort_three(a);
	while (*b)
		push_to_a(a, b);
}
