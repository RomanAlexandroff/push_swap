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

t_bench	*bench_init(bool bench_flag)
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
	bench->disorder_percent = 00.00f;
	return (bench);
}

void	benchmark_mode(t_bench *bench)
{
	int total_ops;

	total_ops = bench->pa + bench->pb +
		bench->sa + bench->sb + bench->ss +
		bench->ra + bench->rb + bench->rr +
		bench->rra + bench->rrb + bench->rrr;
	printf("\nBENCHMARK MODE\nTotal steps: %d\n", total_ops);
	free(bench);
}
