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
	int		nodes_count;

	a = NULL;
	b = NULL;
	if (argc <= 1 || (argc == 2 && !argv[1]))
		return (EXIT_FAILURE);
	else if (argc == 2)
		argv = extract_values(argv[1]);
	if (!argv)								// if malloc fails
		free_and_exit(&a, argv + 1, argc);
	create_stack_safely(&a, argv + 1, argc);
	nodes_count = get_stack_length(a);
	if (!is_sorted(a))
	{
		if (nodes_count == 2)
			swap_a(&a);
		else if (nodes_count == 3)
			sort_three(&a);
		else
			sort_many(&a, &b);
	}
	return (free_stack_mem(&a), EXIT_SUCCESS);
}
