/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:33:00 by roaleksa          #+#    #+#             */
/*   Updated: 2026/05/28 15:09:30 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_bench	*bench_init(bool bench_flag)
{
	t_bench	*bench;

	if (!bench_flag)
		return (NULL);
	bench = malloc(sizeof *bench);
	if (!bench)
		return (NULL);
	bench->enabled = true;
	bench->strategy_name = NULL;
	bench->complexity = NULL;
	bench->sa = 0;
	bench->sb = 0;
	bench->ss = 0;
	bench->pa = 0;
	bench->pb = 0;
	bench->ra = 0;
	bench->rb = 0;
	bench->rr = 0;
	bench->rra = 0;
	bench->rrb = 0;
	bench->rrr = 0;
	bench->total_ops = 0;
	bench->disorder_percent = 00.00f;
	return (bench);
}

static void	mode_dispatcher(t_mode mode, t_node **a, t_node **b)
{
	if (is_sorted(*a))
		return ;
	if (get_stack_length(*a) == 2)
		return (swap_a(a));
	if (mode == SIMPLE_MODE)
		simple_strategy(a, b);
	else if (mode == MEDIUM_MODE)
		medium_sort(a, b);
	else if (mode == COMPLEX_MODE)
		complex_strategy(a, b);
	else
		write(1, "\n  - - Adaptive Sort has been trigerred\n\n", 42);		//adaptive_sort(a, b);				//TODO
}

int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	t_mode	complexity_mode;
	bool	bench_flag;
	t_bench	*bench;

	a = NULL;
	b = NULL;
	if (argc <= 1 || (argc == 2 && !argv[1])) 	// Input validation (to the extend of current possibilities)
		return (EXIT_FAILURE);
	argv = split_arguments(argv + 1, argc - 1);			// Make sure all the given arguments are in their individual strings
	if (!argv)										// If malloc fails, free everything and exit with Error
		free_and_exit(&a, argv);
	if (!set_flags(argv, &complexity_mode, &bench_flag)) 	// if flags are incorrect, free everything and exit with Error
		free_and_exit(&a, argv);
	bench = bench_init(bench_flag);
	if (bench_flag && !bench)							// if malloc fails for bench
		free_and_exit(&a, argv);
	create_stack_safely(&a, argv);						// parse argv arguments into a doubly linked list
	mode_dispatcher(complexity_mode, &a, &b);			// the main sorting work happens in here
	if (bench_flag)
		benchmark_mode(a, b, &bench);                        //TODO
	return (free_stack_mem(&a), EXIT_SUCCESS);
}
