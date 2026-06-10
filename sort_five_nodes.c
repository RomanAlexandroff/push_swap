/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five_nodes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:42:08 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 12:08:30 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ensure_top(t_node **stack, t_node *node, char name)
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
	while (get_stack_length(*a) > 3)
	{
		update_nodes(*a, *b);
		ensure_top(a, get_lowest_value(*a), 'a');
		push_to_b(a, b);
	}
}
