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

#include "push_swap.h"

void	set_benchmark(t_node **a, char *strategy, char *complex, float disorder)
{
	if (!*a || !(*a)->bench)				// if Benchmark mode isn't turned ON
		return ;
	if (strategy != SKIP_STRATEGY)
		(*a)->bench->strategy_name = strategy;
	if (complex != SKIP_COMPLEXITY)
		(*a)->bench->complexity = complex;
	if (disorder != SKIP_DISORDER)
		(*a)->bench->disorder = disorder;
}

t_bench	*bench_init(bool bench_flag)
{
	t_bench	*bench;

	if (!bench_flag)
		return (NULL);
	bench = malloc(sizeof *bench);
	if (!bench)
		return (NULL);
	bench->enabled = true;
	bench->disorder = 00.00f;			// get from mode_dispatcher()
	bench->strategy_name = NULL;		// get from each individual sorting strategy
	bench->complexity = NULL;			// get from each individual sorting strategy
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

void	benchmark_mode(t_bench *bench)
{
	int total_ops;

	if (bench == NULL)
		return ;
	if (bench->strategy_name == NULL)			// in case push_swap was given already sorted numbers
		bench->strategy_name = "--";
	if (bench->complexity == NULL)				// in case push_swap was given already sorted numbers
		bench->complexity = "--";
	total_ops = bench->rra + bench->rrb + bench->rrr + bench->sb + bench->ss
		+ bench->ra + bench->rb + bench->rr + bench->pa + bench->pb + bench->sa;
	render_benchmark(bench, total_ops);
	free(bench);
}
