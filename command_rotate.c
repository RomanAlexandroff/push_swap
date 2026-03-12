#include "push_swap.h"

static void	ft_rotate(t_node **stack)
{
	t_node	*last_node;
	int		length;

	length = ft_get_stack_length(*stack);
	if (*stack == NULL || stack == NULL || length == 1)
		return ;
	last_node = ft_get_last_node(*stack);
	last_node->node_after = *stack;
	*stack = (*stack)->node_after;
	(*stack)->node_before = NULL;
	last_node->node_after->node_before = last_node;
	last_node->node_after->node_after = NULL;
}	

void	ft_rotate_a(t_node **a)
{
	ft_rotate(a);
	write(1, "ra\n", 3);
}

void	ft_rotate_b(t_node **b)
{
	ft_rotate(b);
	write(1, "rb\n", 3);
}

void	ft_rotate_both(t_node **a, t_node **b)
{
	ft_rotate(a);
	ft_rotate(b);
	write(1, "rr\n", 3);
}
