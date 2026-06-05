/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adaptive_strategy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 11:45:58 by ccrucian          #+#    #+#             */
/*   Updated: 2026/06/05 12:13:34 by ccrucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	adaptive_strategy(t_node **a, t_node **b, int nodes_count)
{
	float	disorder;

	disorder = compute_disorder(*a, nodes_count);
	if (disorder < 0.2)
		simple_strategy(a, b);
	else if (disorder >= 0.2 && disorder < 0.5)
		medium_sort(a, b);
	else if (disorder >= 0.5)
		complex_strategy(a, b);
	return ;
}
