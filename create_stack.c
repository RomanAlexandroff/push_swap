#include "push_swap.h"

static void	add_new_node(t_node **stack, int value)
{
	t_node	*new_node;
	t_node	*last_node;

	if (stack == NULL)
		return ;
	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		return ;
	new_node->node_after = NULL;
	new_node->value = value;
	if (*stack == NULL)
	{
		*stack = new_node;
		new_node->node_before = NULL;
	}
	else
	{
		last_node = get_last_node(*stack);
		last_node->node_after = new_node;
		new_node->node_before = last_node;
	}
}

static long	ft_atod(const char *str)
{
	long	result;
	int		sign;
	int		i;

	result = 0;
	sign = +1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (sign * result);
}

void	create_stack_safely(t_node **a, char **argv, int argc)
{
	long	value;
	int		i;

	value = 0;
	i = 0;
	while (argv[i])
	{
		if (!characters_check(argv[i]))
			free_and_exit(a, argv, argc);
		value = ft_atod(argv[i]);
		if (value < INT_MIN || value > INT_MAX)
			free_and_exit(a, argv, argc);
		if (!ft_duplicates_check(*a, (int)value))
			free_and_exit(a, argv, argc);
		add_new_node(a, (int)value);
		i++;
	}
	if (argc == 2)
		free_argv_mem(argv);
}
