#include "push_swap.h"

/*
 * Finds node with the largest value
*/
static t_node	*ft_get_largest_node(t_node *stack)
{
	int		largest_value;
	t_node	*largest_node;

	largest_value = INT_MIN;
    if (stack == NULL)
		return (NULL);
	while (stack)
	{
		if (stack->value > largest_value)
		{
			largest_value = stack->value;
			largest_node = stack;
		}
		stack = stack->node_after;
	}
	return (largest_node);
}

void	ft_sort_three(t_node **a)
{
	t_node	*largest_node;

	largest_node = ft_get_largest_node(*a);
	if (*a == largest_node)
		ft_rotate_a(a);
	else if ((*a)->node_after == largest_node)
		ft_reverse_a(a);
	if ((*a)->value > (*a)->node_after->value)
		ft_swap_a(a);
}
