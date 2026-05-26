/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_reverse.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:32:23 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:32:23 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

double  compute_disorder(t_node *a, int nodes_count)
{
    t_node  *j; 
    long total_compares;
    long unsorted_pairs;
    double  disorder;

    if (!a || nodes_count <= 1)
        return (0.0);
    unsorted_pairs = 0;
    total_compares = 0;
    while (a)
    {
        j = a->node_after;
        while (j)
        {
            if (a->value > j->value)
                unsorted_pairs++;
            total_compares++;
            j = j->node_after;
        }
        a = a->node_after;
    }
    disorder = (double)unsorted_pairs/total_compares;
    return (disorder);
}