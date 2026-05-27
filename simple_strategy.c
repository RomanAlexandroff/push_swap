#include "push_swap.h"

void	simple_strategy(t_node **a, t_node **b)
{
	t_node	*smallest_node;

	while (*a)
	{
		smallest_node = get_lowest_value(*a);
		position_update(*a);
		while (*a != smallest_node)
		{
			if (smallest_node->top_half_flag)
				rotate_a(a);
			else
				reverse_a(a);
		}
		push_to_b(a, b);
	}
	while (*b)
		push_to_a(a, b);
}
