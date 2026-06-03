/* ************************************************************************** */
/*									      */
/*							  :::	   ::::::::   */
/*   compute_disorder.c                                 :+:      :+:    :+:   */
/*						      +:+ +:+	      +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>	    +#+  +:+	   +#+	      */
/*						  +#+#+#+#+#+	+#+	      */
/*   Created: 2026/05/28 14:53:59 by ccrucian	       #+#    #+#	      */
/*   Updated: 2026/05/28 15:09:21 by ccrucian         ###   ########.fr       */
/*									      */
/* ************************************************************************** */

#include "push_swap.h"

static void	put_float(int n)
{
	char	c;

	if (n >= 10)
		put_float(n / 10);
	c = (n % 10) + '0';
	write(1, &c, 1);
}

/* 
 * Prints the disorder value as a percentage with two decimal digits.
 * Value is rounded by converting the float into an integer. 
*/

void	print_disorder_percent(float disorder)
{
	int	nb;
	int	integer;
	int	decimal;

	nb = (disorder * 10000) + 0.5;
	integer = nb / 100;
	decimal = nb % 100;
	put_float(integer);
	write(1, ".", 1);
	if (decimal == 0)
		write(1, "00", 2);
	else
		put_float(decimal);
	write(1, "%", 1);
}

/* 
 * Computes how many pairs of nodes are in the wrong order.
 * Returns the ratio between wrong pairs(mistakes) and total compared pairs. 
*/

float	compute_disorder(t_node *a, int nodes_count)
{
	t_node	*j;
	long	total_pairs;
	long	mistakes;
	double	disorder;

	if (!a || nodes_count <= 1)
		return (0.0);
	mistakes = 0;
	total_pairs = 0;
	while (a)
	{
		j = a->node_after;
		while (j)
		{
			if (a->value > j->value)
				mistakes++;
			total_pairs++;
			j = j->node_after;
		}
		a = a->node_after;
	}
	disorder = (float)mistakes / total_pairs;
	return (disorder);
}

int	main()
{
	print_disorder_percent(0.523);
	write(1, "\n", 1);
	print_disorder_percent(1);
	write(1, "\n", 1);
	print_disorder_percent(0);
	write(1, "\n", 1);
	print_disorder_percent(0.50);
	write(1, "\n", 1);
	print_disorder_percent(0.51);
	write(1, "\n", 1);
	print_disorder_percent(0.510);
	write(1, "\n", 1);
	print_disorder_percent(0.511);
	write(1, "\n", 1);
	return (0);

}
