/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_rendering.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-06 20:41:13 by roaleksa          #+#    #+#             */
/*   Updated: 2026-06-06 20:41:13 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	print_number(unsigned int num)
{
	char	c;

    if (num >= 10)
        print_number(num / 10);
    c = (num % 10) + '0';
    write(FD_STDERR, &c, 1);
}

/* 
 * Prints the disorder value as a percentage with two decimal digits.
 * Value is rounded by converting the float into an integer. 
*/
static void	print_disorder_percent(float disorder)
{
	int	nb;
	int	integer;
	int	decimal;

	nb = (disorder * 10000) + 0.5;
	integer = nb / 100;
	decimal = nb % 100;
	print_number(integer);
	write(FD_STDERR, ".", 1);
	if (decimal == 0)
		write(FD_STDERR, "00", 2);
	else
		print_number(decimal);
	write(FD_STDERR, "%", 1);
}

static void print_string(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(FD_STDERR, &str[i], 1);
        i++;
    }
}

static void print_ops_stats(char *label, unsigned int ops_num)
{
    print_string(label);
    print_number(ops_num);
}

// [bench] disorder:    40.00%
// [bench] strategy:    Adaptive / O(n√n)
// [bench] total_ops:    13
// [bench] sa:   0   sb:   0   ss:   0   pa:   5   pb:   5
// [bench] ra:   2   rb:   1   rr:   0   rra:   0   rrb:   0   rrr:   0

void	render_benchmark(t_bench *bench, int total_ops)
{
	write(FD_STDERR, "[bench] disorder:    ", 21);
	print_disorder_percent(bench->disorder);
	write(FD_STDERR, "\n[bench] strategy:    ", 22);
    print_string(bench->strategy_name);
    write(FD_STDERR, " / ", 3);
    print_string(bench->complexity);
	write(FD_STDERR, "\n[bench] total_ops:    ", 23);
	print_number(total_ops);
	print_ops_stats("\n[bench] sa:   ", bench->sa);
	print_ops_stats("   sb:   ", bench->sb);
	print_ops_stats("   ss:   ", bench->ss);
	print_ops_stats("   pa:   ", bench->pa);
	print_ops_stats("   pb:   ", bench->pb);
	print_ops_stats("\n[bench] ra:   ", bench->ra);
	print_ops_stats("   rb:   ", bench->rb);
	print_ops_stats("   rr:   ", bench->rr);
	print_ops_stats("   rra:   ", bench->rra);
	print_ops_stats("   rrb:   ", bench->rrb);
	print_ops_stats("   rrr:   ", bench->rrr);
	write(FD_STDERR, "\n", 1);
}
