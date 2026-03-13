/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:32:34 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:32:34 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 * TO:DO: explain brackets in (*top_node)->node_after
*/
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
	write(1, "sa\n", 3);
}

void	swap_b(t_node **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

void	swap_both(t_node **a, t_node **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}
