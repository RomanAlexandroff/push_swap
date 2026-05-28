#include "push_swap.h"

/*
 *Assigns an index from 0 to length - 1 to each node based
 * on the relative order of its value, in order to compress
 * the values in an easier way to process them.
 */

static void	assign_index(t_node *stack)
{
	t_node	*current;
	t_node	*i_node;

	current = stack;
	while (current)
	{
		current->index = 0
		i_node = stack;
		while (i_node)
		{
			if (current->value > i_node->value)
				current->index++;
			i_node = i_node->node_after;
		}
		current = current->node_after;
	}
}

/*
 * Calculate the maximum number of bits needed to represent 
 * the biggest index in the stack. 
*/

static int	get_max_bits(t_node *stack)
{
	int	max_bits;
	int	max_index;

	max_index = a->index;
	max_bits = 1;
	while (a)
	{
		if (a->index > max_index)
			max_index = a->index;
		a = a->node_after;
	}
	while (max_index > 0)
	{
		max_index = max_index / 2;
		max_bits++;
	}
	return (max_bits);
}

void	complex_strategy(t_node **a, t_node **b)
{
	int	length;
	int	max_bits;

	update_nodes
	length = get_stack_length(*a);
	assign_index(*a);
	max_bits = get_max_bits(*a);
}
