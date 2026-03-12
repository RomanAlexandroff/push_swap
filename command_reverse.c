#include "push_swap.h"

static void	reverse(t_node **stack)
{
	t_node	*last_node;
	int		length;

	length = get_stack_length(*stack);
	if (*stack == NULL || stack == NULL || length == 1)
		return ;
	last_node = get_last_node(*stack);
	last_node->node_before->node_after = NULL;
	last_node->node_after = *stack;
	last_node->node_before = NULL;
	*stack = last_node;
	last_node->node_after->node_before = last_node;
}

void	reverse_a(t_node **a)
{
	reverse(a);
	write(1, "rra\n", 4);
}

void	reverse_b(t_node **b)
{
	reverse(b);
	write(1, "rrb\n", 4);
}

void	reverse_both(t_node **a, t_node **b)
{
	reverse(a);
	reverse(b);
	write(1, "rrr\n", 4);
}
