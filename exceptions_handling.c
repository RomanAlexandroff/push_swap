
#include "push_swap.h"

/*
 * Looks for unacceptable characters
*/
int	characters_check(char *input)
{
	if (!(*input == '+'
			|| *input == '-'
			|| (*input >= '0' && *input <= '9')))
		return (false);
	if ((*input == '+'
			|| *input == '-')
		&& !(input[1] >= '0' && input[1] <= '9'))
		return (false);
	while (*++input)
	{
		if (!(*input >= '0' && *input <= '9'))
			return (false);
	}
	return (true);
}

int	duplicates_check(t_node *a, int input)
{
	if (a == NULL)
		return (true);
	while (a)
	{
		if (a->value == input)
			return (false);
		a = a->node_after;
	}
	return (true);
}

void	free_argv_mem(char **argv)
{
	int	i;

	i = -1;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv - 1);
}

void	free_stack_mem(t_node **stack)
{
	t_node	*buffer;
	t_node	*current;

	if (stack == NULL)
		return ;
	current = *stack;
	while (current)
	{
		buffer = current->node_after;
		free(current);
		current = buffer;
	}
	*stack = NULL;
}

void	free_and_exit(t_node **a, char **argv, int argc)
{
	free_stack_mem(a);
	if (argc == 2)
		free_argv_mem(argv);
	write(2, "Error\n", 6);
	exit(1);
}
