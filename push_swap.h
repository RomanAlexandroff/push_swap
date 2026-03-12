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

char	**extract_values(char *user_input);
void	create_stack_safely(t_node **a, char **argv, int argc);
int	    characters_check(char *input);
int	    duplicates_check(t_node *a, int input);
void	free_argv_mem(char **argv);
void	free_stack_mem(t_node **stack);
void	free_and_exit(t_node **a, char **argv, int argc);
t_node	*get_last_node(t_node *node);
t_node	*get_lowest_value(t_node *stack);
t_node	*find_next_to_solve(t_node *stack);
int	    get_stack_length(t_node *stack);
bool	is_sorted(t_node *stack);
void	position_update(t_node *stack);
void	solving_cost_update(t_node *a, t_node *b);
void	next_to_solve_update(t_node *b);
void	update_nodes(t_node *a, t_node *b);
void	ensure_top(t_node **stack, t_node *node, char name);
void	sort_three(t_node **a);
void	sort_many(t_node **a, t_node **b);
void	push_to_a(t_node **a, t_node **b);
void	push_to_b(t_node **a, t_node **b);
void	swap_a(t_node **a);
void	swap_b(t_node **b);
void	swap_both(t_node **a, t_node **b);
void	rotate_a(t_node **a);
void	rotate_b(t_node **b);
void	rotate_both(t_node **a, t_node **b);
void	reverse_a(t_node **a);
void	reverse_b(t_node **b);
void	reverse_both(t_node **a, t_node **b);

#endif

/*			TO-DO LIST
	- create README.md as per project subject
	- check if it compiles on Ubuntu
	- run Tests (make test)
	- make sure the subject does not have any changes, that I have not implemented
	- add heads to all the files
	- run Norminette (make norm) with all the flags and fix whatever it says
	- THIS PROJECT REQUIRES MAKEFILE TO BE SUBMITED !
		get_next_line did not need you to submit a Makefile, but it was an exception,
		push_swap does require a Makifile to be submited.
*/
