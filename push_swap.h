/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:33:08 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 12:09:12 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <unistd.h>
# include <stddef.h>
# include <stdio.h>

# define SKIP_STRATEGY		0
# define SKIP_COMPLEXITY	0
# define SKIP_DISORDER		404.0f
# define FD_STDOUT			1
# define FD_STDERR			2

typedef enum e_mode
{
	SIMPLE_MODE,
	MEDIUM_MODE,
	COMPLEX_MODE,
	ADAPTIVE_MODE,
}			t_mode;

typedef struct s_bench
{
	bool			enabled;
	float			disorder;
	char			*strategy_name;
	char			*complexity;
	unsigned int	sa;
	unsigned int	sb;
	unsigned int	ss;
	unsigned int	pa;
	unsigned int	pb;
	unsigned int	ra;
	unsigned int	rb;
	unsigned int	rr;
	unsigned int	rra;
	unsigned int	rrb;
	unsigned int	rrr;
}				t_bench;

typedef struct s_node
{
	int				value;
	int				node_position;
	int				index;
	struct s_node	*node_before;
	struct s_node	*node_after;
	struct s_node	*destination;
	bool			top_half_flag;
	int	    		solving_cost;
	bool			next_to_solve;
	t_bench			*bench;
}				t_node;

/* Initialization and User Arguments Parsing */
char	**split_arguments(char **argv, int argc);
int		count_arguments(char *argv);
int		find_arguments(char **argv, int argc);
void	create_stack_safely(t_node **a, char **argv, t_bench *bench);
int		characters_check(char *input);
int		duplicates_check(t_node *a, int input);
bool	set_flags(char **argv, t_mode *complexity_mode, bool *bench_flag);
t_bench	*bench_init(bool bench_flag);

/* Sorting Strategies */
void	adaptive_strategy(t_node **a, t_node **b, int size, float disorder);
void	simple_strategy(t_node **a, t_node **b);
void	medium_strategy(t_node **a, t_node **b, int size);
void	complex_strategy(t_node **a, t_node **b);
void	sort_three(t_node **a);
void	sort_five(t_node **a, t_node **b);

/* Sorting Helper Functions */
float	compute_disorder(t_node *a, int nodes_count);
int		get_stack_length(t_node *stack);
bool	is_sorted(t_node *stack);
void	move_to_top_a(t_node **a, int pos);
void	move_to_top_b(t_node **b, int pos);
void	push_chunk(t_node **a, t_node **b, int min, int max);
t_node	*get_last_node(t_node *node);
t_node	*get_lowest_value(t_node *stack);
int		ft_sqrt(int num);
void	update_nodes(t_node *a, t_node *b);

/* Stack Sorting Orepations */
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

/* Handling Exceptions and Cleaning-Up */
void	free_argv_mem(char **argv);
void	free_stack_mem(t_node **stack);
void	free_and_exit(t_node **a, char **argv);

/* Debugging */
void	benchmark_mode(t_bench *bench);
void	set_benchmark(t_node **a, char *strategy, char *complex,
			float disorder);
void	render_benchmark(t_bench *bench, int total_ops);

#endif
