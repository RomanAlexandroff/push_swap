/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:32:34 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/05 14:56:02 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_node **top_node)
{
	int	length;

	length = 0;
	length = get_stack_length(*top_node);
	if (*top_node == NULL || top_node == NULL || length == 1)
		return ;
	*top_node = (*top_node)->node_after;
/* working with the 1st node */
	(*top_node)->node_before->node_before = *top_node;
	(*top_node)->node_before->node_after = (*top_node)->node_after;
/* working with the 3rd node */
	if ((*top_node)->node_after)
		(*top_node)->node_after->node_before = (*top_node)->node_before;
/*  working with the 2nd node  */
	(*top_node)->node_after = (*top_node)->node_before;
	(*top_node)->node_before = NULL;
}

void	swap_a(t_node **a)
{
	swap(a);
	if (*a && (*a)->bench)
		(*a)->bench->sa++;
	write(FD_STDOUT, "sa\n", 3);
}

void	swap_b(t_node **b)
{
	swap(b);
	if (*b && (*b)->bench)
		(*b)->bench->sb++;
	write(FD_STDOUT, "sb\n", 3);
}

void	swap_both(t_node **a, t_node **b)
{
	swap(a);
	swap(b);
	if (*a && (*a)->bench)
		(*a)->bench->ss++;
	write(FD_STDOUT, "ss\n", 3);
}
