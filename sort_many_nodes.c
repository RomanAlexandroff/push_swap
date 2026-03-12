#include "push_swap.h"

// static void	rotate_both(t_node **a, t_node **b, t_node *node)
// {
// 	while (*a != node->destination && *b != node)
// 		ft_rotate_both(a, b);
// 	ft_position_update(*a);
// 	ft_position_update(*b);
// }

// static void	reverse_both(t_node **a, t_node **b, t_node *node)
// {
// 	while (*a != node->destination && *b != node)
// 		ft_reverse_both(a, b);
// 	ft_position_update(*a);
// 	ft_position_update(*b);
// }

void	ft_ensure_top(t_node **stack, t_node *node, char name)
{
	while (*stack != node)
	{
		if (name == 'a')
		{
			if (node->top_half_flag)
				ft_rotate_a(stack);
			else
				ft_reverse_a(stack);
		}
		else if (name == 'b')
		{
			if (node->top_half_flag)
				ft_rotate_b(stack);
			else
				ft_reverse_b(stack);
		}	
	}
}

static void	ft_solve_node(t_node **a, t_node **b)
{
	t_node	*node;

	node = ft_find_next_to_solve(*b);
	if (node->top_half_flag && node->destination->top_half_flag)
    {
	    while (*a != node->destination && *b != node)
		    ft_rotate_both(a, b);
	    ft_position_update(*a);
	    ft_position_update(*b);
    }
	else if (!(node->top_half_flag) && !(node->destination->top_half_flag))
    {
	    while (*a != node->destination && *b != node)
		    ft_reverse_both(a, b);
	    ft_position_update(*a);
	    ft_position_update(*b);
    }
	ft_ensure_top(b, node, 'b');
	ft_ensure_top(a, node->destination, 'a');
	ft_push_to_a(a, b);
}

// static void	ft_sort_five(t_node **a, t_node **b)
// {
// 	while (ft_get_stack_length(*a) > 3)
// 	{
// 		ft_update_nodes(*a, *b);
// 		ft_ensure_top(a, ft_get_lowest_value(*a), 'a');
// 		ft_push_to_b(a, b);
// 	}
// }

void	ft_sort_many(t_node **a, t_node **b)
{
	int		length;
    t_node	*smallest_node;

	length = 0;
    length = ft_get_stack_length(*a);
	// if (length == 5)
	// 	ft_sort_five(a, b);						// TO:DO. выяснить нахрена это нужно отдельной функцией
	// else
	// {
		while (length-- > 3)
			ft_push_to_b(a, b); 
//	}
	ft_sort_three(a);
	while (*b)
	{
		ft_update_nodes(*a, *b);
		ft_solve_node(a, b);
	}
	ft_position_update(*a);
	smallest_node = ft_get_lowest_value(*a);
	if (smallest_node->top_half_flag)
		while (*a != smallest_node)
			ft_rotate_a(a);
	else
		while (*a != smallest_node)
			ft_reverse_a(a);
}
