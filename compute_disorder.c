/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2026/05/28 14:53:59 by ccrucian	       #+#    #+#	      */
/*   Updated: 2026/05/28 15:09:21 by ccrucian         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "push_swap.h"

/* 
 * Computes how many pairs of nodes are in the wrong order.
 * Returns the ratio between wrong pairs(mistakes) and total compared pairs. 
*/
float	compute_disorder(t_node *a, int nodes_count)
{
	t_node	*j;
	long	total_pairs;
	long	mistakes;
	float	disorder;

	if (!a || nodes_count <= 1)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	while (a)
	{
		j = a->node_after;
		while (j)
		{
			if (a->value > j->value)
				mistakes++;
			total_pairs++;
			j = j->node_after;
		}
		a = a->node_after;
	}
	disorder = (float)mistakes / total_pairs;
	return (disorder);
}
