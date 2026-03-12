#include "push_swap.h"

static void	ft_reverse(t_node **stack)
{
	t_node	*last_node;
	int		length;

	length = ft_get_stack_length(*stack);
	if (*stack == NULL || stack == NULL || length == 1)
		return ;
	last_node = ft_get_last_node(*stack);
	last_node->node_before->node_after = NULL;
	last_node->node_after = *stack;
	last_node->node_before = NULL;
	*stack = last_node;
	last_node->node_after->node_before = last_node;
}

void	ft_reverse_a(t_node **a)
{
	ft_reverse(a);
	write(1, "rra\n", 4);
}

void	ft_reverse_b(t_node **b)
{
	ft_reverse(b);
	write(1, "rrb\n", 4);
}

void	ft_reverse_both(t_node **a, t_node **b)
{
	ft_reverse(a);
	ft_reverse(b);
	write(1, "rrr\n", 4);
}
