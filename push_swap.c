/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:33:00 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 12:25:19 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
	Dynamically chooses the sorting strategy based
	on the current disorder value: simplier
	strategy for less disordered number set and
	more complex strategy for high disorder.
	set_benchmark() must be at the bottom, so it
	overwrites the strategy name from the previous
	strategy call.
*/
void	adaptive_strategy(t_node **a, t_node **b, int size, float disorder)
{
	if (disorder < 0.2f)
		simple_strategy(a, b);
	else if (disorder >= 0.2f && disorder < 0.5f)
		medium_strategy(a, b, size);
	else if (disorder >= 0.5f)
		complex_strategy(a, b);
	set_benchmark(a, "Adaptive", SKIP_COMPLEXITY, SKIP_DISORDER);
}

/*
	Calculates the disorder before any operations,
	cancels sorting if the stack is already sorted,
	switches between the sorting strategies based
	on the flag set by the User, using the adaptive
	strategy as the default sorting approach.
*/
static void	mode_dispatcher(t_mode mode, t_node **a, t_node **b)
{
	float	disorder;
	int		size;

	size = get_stack_length(*a);
	disorder = compute_disorder(*a, size);
	set_benchmark(a, SKIP_STRATEGY, SKIP_COMPLEXITY, disorder);
	if (is_sorted(*a))
		return ;
	if (size == 3)
	{
		sort_three(a);
		return ;
	}
	if (size == 5)
	{
		sort_five(a, b);
		return ;
	}
	if (mode == SIMPLE_MODE)
		simple_strategy(a, b);
	else if (mode == MEDIUM_MODE)
		medium_strategy(a, b, size);
	else if (mode == COMPLEX_MODE)
		complex_strategy(a, b);
	else
		adaptive_strategy(a, b, size, disorder);
}

/*
	Program entry point. Orchestrates the full lifecycle:
		- immediately rejects empty input,
		- ensures every argument is in individual string,
		- parses sorting and benchmark flags from argv,
		- initializes the benchmark struct if needed,
		- parses only number arguments into stack A,
		- calls to run the appropriate sorting strategy,
		- calls to print the benchmark stats if needed,
		- frees allocated resources and exits.
 	On any earlier failure, handles cleanup and exits.
 */
int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	t_mode	complexity_mode;
	bool	bench_flag;
	t_bench	*bench;

	a = NULL;
	b = NULL;
	if (argc <= 1 || (argc == 2 && !argv[1]))
		return (EXIT_FAILURE);
	argv = split_arguments(argv + 1, argc - 1);
	if (!argv)
		free_and_exit(&a, argv);
	if (!set_flags(argv, &complexity_mode, &bench_flag))
		free_and_exit(&a, argv);
	bench = bench_init(bench_flag);
	if (bench_flag && !bench)
		free_and_exit(&a, argv);
	create_stack_safely(&a, argv, bench);
	mode_dispatcher(complexity_mode, &a, &b);
	benchmark_mode(bench);
	return (free_stack_mem(&a), EXIT_SUCCESS);
}
