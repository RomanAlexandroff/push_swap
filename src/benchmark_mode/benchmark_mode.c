/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 18:22:25 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/05 15:52:03 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

/*
	Universal setter function for benchmark values.
	Helps prevent overcluttering the codebase with
	excessive debug logic. It is safe to be called
	from anywhere at any time as it can cancel its
	own execution if the Benchmark mode is not ON.
*/
void	set_benchmark(t_node **a, char *strategy, char *complex, float disorder)
{
	if (!*a || !(*a)->bench)
		return ;
	if (strategy != SKIP_STRATEGY)
		(*a)->bench->strategy_name = strategy;
	if (complex != SKIP_COMPLEXITY)
		(*a)->bench->complexity = complex;
	if (disorder != SKIP_DISORDER)
		(*a)->bench->disorder = disorder;
}

/*
	Dynamically allocates memory for the benchmark
	struct, sets all stats to their initial values.
	It does its own Benchmark mode activation check
	before executing. The caller is reliable for
	freeing the allocated memory.
*/
t_bench	*bench_init(bool bench_flag)
{
	t_bench	*bench;

	if (!bench_flag)
		return (NULL);
	bench = malloc(sizeof (*bench));
	if (!bench)
		return (NULL);
	bench->enabled = true;
	bench->disorder = 00.00f;
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
	return (bench);
}

/*
	API to render all the gathered debug stats
	into a comprehensive table to be outputted
	to stderr. Resets all the unused stats to
	a printable format, calculates the total
	number of sorting operations made, calls
	for the renderer to print everything out,
	frees dynamically allocated bench struct.
	Executes only if the bench flag is set.
*/
void	benchmark_mode(t_bench *bench)
{
	int	total_ops;

	if (bench == NULL)
		return ;
	if (bench->strategy_name == NULL)
		bench->strategy_name = "--";
	if (bench->complexity == NULL)
		bench->complexity = "--";
	total_ops = bench->rra + bench->rrb + bench->rrr + bench->sb + bench->ss
		+ bench->ra + bench->rb + bench->rr + bench->pa + bench->pb + bench->sa;
	render_benchmark(bench, total_ops);
	free(bench);
}
