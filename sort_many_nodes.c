#include "push_swap.h"

void	ensure_top(t_node **stack, t_node *node, char name)
{
	while (*stack != node)
	{
		if (name == 'a')
		{
			if (node->top_half_flag)
				rotate_a(stack);
			else
				reverse_a(stack);
		}
		else if (name == 'b')
		{
			if (node->top_half_flag)
				rotate_b(stack);
			else
				reverse_b(stack);
		}	
	}
}

static void	solve_node(t_node **a, t_node **b)
{
	t_node	*node;

	node = find_next_to_solve(*b);
	if (node->top_half_flag && node->destination->top_half_flag)
    {
	    while (*a != node->destination && *b != node)
		    rotate_both(a, b);
	    position_update(*a);
	    position_update(*b);
    }
	else if (!(node->top_half_flag) && !(node->destination->top_half_flag))
    {
	    while (*a != node->destination && *b != node)
		    reverse_both(a, b);
	    position_update(*a);
	    position_update(*b);
    }
	ensure_top(b, node, 'b');
	ensure_top(a, node->destination, 'a');
	push_to_a(a, b);
}

// static void	sort_five(t_node **a, t_node **b)
// {
// 	while (get_stack_length(*a) > 3)
// 	{
// 		update_nodes(*a, *b);
// 		ensure_top(a, ft_get_lowest_value(*a), 'a');
// 		push_to_b(a, b);
// 	}
// }

void	sort_many(t_node **a, t_node **b)
{
	int		length;
    t_node	*smallest_node;

	length = 0;
    length = get_stack_length(*a);
	// if (length == 5)
	// 	sort_five(a, b);						// TO:DO. выяснить нахрена это нужно отдельной функцией
	// else
	// {
		while (length-- > 3)
			push_to_b(a, b); 
//	}
	sort_three(a);
	while (*b)
	{
		update_nodes(*a, *b);
		solve_node(a, b);
	}
	position_update(*a);
	smallest_node = get_lowest_value(*a);
	if (smallest_node->top_half_flag)
		while (*a != smallest_node)
			rotate_a(a);
	else
		while (*a != smallest_node)
			reverse_a(a);
}
