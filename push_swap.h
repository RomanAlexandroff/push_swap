#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>

typedef struct s_node
{
	int				value;
	int				node_position;
	struct s_node	*node_before;
	struct s_node	*node_after;
    struct s_node	*destination;
    int	    		solving_cost;
	bool			top_half_flag;
	bool			next_to_solve;
}				t_node;

char	**ft_extract_values(char *input);
void	ft_create_stack_safely(t_node **a, char **argv, int argc);
int	    ft_characters_check(char *input);
int	    ft_duplicates_check(t_node *a, int input);
void	ft_free_argv_mem(char **argv);
void	ft_free_stack_mem(t_node **stack);
void	ft_free_and_exit(t_node **a, char **argv, int argc);
t_node	*ft_get_last_node(t_node *node);
t_node	*ft_get_lowest_value(t_node *stack);
t_node	*ft_find_next_to_solve(t_node *stack);
int	    ft_get_stack_length(t_node *stack);
bool	ft_is_sorted(t_node *stack);
void	ft_position_update(t_node *stack);
void	ft_solving_cost_update(t_node *a, t_node *b);
void	ft_next_to_solve_update(t_node *b);
void	ft_update_nodes(t_node *a, t_node *b);
void	ft_ensure_top(t_node **stack, t_node *node, char name);
void	ft_sort_three(t_node **a);
void	ft_sort_many(t_node **a, t_node **b);
void	ft_push_to_a(t_node **a, t_node **b);
void	ft_push_to_b(t_node **a, t_node **b);
void	ft_swap_a(t_node **a);
void	ft_swap_b(t_node **b);
void	ft_swap_both(t_node **a, t_node **b);
void	ft_rotate_a(t_node **a);
void	ft_rotate_b(t_node **b);
void	ft_rotate_both(t_node **a, t_node **b);
void	ft_reverse_a(t_node **a);
void	ft_reverse_b(t_node **b);
void	ft_reverse_both(t_node **a, t_node **b);

#endif
