#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
    int     nodes_count;

	a = NULL;
	b = NULL;
    nodes_count = 0;
	if (argc <= 1 || (argc == 2 && !argv[1][0]))
		return (1);
	else if (argc == 2)
		argv = ft_extract_values(argv[1]);
	ft_create_stack_safely(&a, argv + 1, argc);
    nodes_count = ft_get_stack_length(a);
	if (!ft_is_sorted(a))
	{
		if (nodes_count == 2)
			ft_swap_a(&a); 
		else if (nodes_count == 3)
			ft_sort_three(&a);
		else
			ft_sort_many(&a, &b);
	}
	ft_free_stack_mem(&a);
	return (0);
}
