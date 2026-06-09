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

/*
	Computes integer square root of num.
*/
int	ft_sqrt(int num)
{
	int	low;
	int	high;
	int	middle;
	int	result;

	if (num <= 0)
		return (0);
	low = 1;
	high = num;
	result = 1;
	while (low <= high)
	{
		middle = (low + high) / 2;
		if ((long)middle * middle <= num)
		{
			result = middle;
			low = middle + 1;
		}
		else
			high = middle - 1;
	}
	return (result);
}
