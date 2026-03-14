/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:33:00 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:33:00 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
    int     nodes_quantity;

	a = NULL;
	b = NULL;
    nodes_quantity = 0;
	if (argc <= 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = extract_values(argv[1]);
	create_stack_safely(&a, argv + 1, argc);
    nodes_quantity = get_stack_length(a);
	if (!is_sorted(a))
	{
		if (nodes_quantity == 2)
			swap_a(&a); 
		else if (nodes_quantity == 3)
			sort_three(&a);
		else
			sort_many(&a, &b);
	}
	free_stack_mem(&a);
	return (0);
}
