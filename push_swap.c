/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:33:00 by roaleksa          #+#    #+#             */
/*   Updated: 2026/05/28 15:09:30 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	mode_dispatcher(t_mode mode, t_node **a, t_node **b)
{
	if (is_sorted(a))
		return ;
	if (get_stack_length(a) == 2)
			return (swap_a(*a));
	if (mode == SIMPLE_MODE)
		simple_sort(*a, *b);				//TODO
	else if (mode == MEDIUM_MODE)
		medium_sort(*a, *b);				//TODO
	else if (mode == COMPLEX_MODE)
		complex_sort(*a, *b);				//TODO
	else
		adaptive_sort(*a, *b);				//TODO
}

int	main(int argc, char **argv)
{
	t_node	*a;
	t_node	*b;
	t_mode	complexity_mode;
	bool	bench_flag;	

	a = NULL;
	b = NULL;
	if (argc <= 1 || (argc == 2 && !argv[1])) 	// Input validation (to the extend of current possibilities)
		return (EXIT_FAILURE);
	argv = split_arguments(argv + 1, argc - 1);			// Make sure all the given arguments are in their individual strings
	if (!argv)										// If malloc fails, free everything and exit with Error
		free_and_exit(&a, argv + 1, argc);
	if (!set_flags(argv, &complexity_mode, &bench_flag)) 	// if flags are incorrect, free everything and exit with Error
		free_and_exit(&a, argv + 1, argc);
	create_stack_safely(&a, argv + 1, argc);			// parse argv arguments into a doubly linked list
	mode_dispatcher(complexity_mode, &a, &b);			// the main sorting work happens in here
	if (bench_flag)
		benchmark_mode(a, b);						//TODO
	return (free_stack_mem(&a), EXIT_SUCCESS);
}








/*
	Goal: implement parsing the 4 algorithm flags (and a missing algorithm flag scenario)
		+ the benchmark mode flag from argv array and the strategy selection
		
	Additional Info:

	All the selector flags to implement:
		--simple
		--medium
		--complex
		--adaptive
		--bench
	Any selector flag should work regardless of input size or disorder.
	Missing algorithm flag scenario == using the --adaptive algorithm flag,
		according to the subject.
	Using multiple algorithm flags in one call shall result in an Error message
		and program exit.
	Misspelling any selector flag shall result in an Error message and program
		exit.
	If no parameters are specified, the program must not display anything and
		give the prompt back, even if selector flags are given correctly.
	Usage examples (Terminal prompts):
		./push_swap 2 1 3 6 5 8				(adaptive algorithm by default, no benchmark, argc == 7)
		ARG="4 67 3 87 23"; ./push_swap --adaptive $ARG | wc -l
											(adaptive algorithm explicitly, no benchmark, argc == 7)
		./push_swap --simple 5 4 3 2 1		(simple algorithm explicitly, no benchmark, argc == 7)
		ARG="4 67 3 87 23"; ./push_swap --complex $ARG | ./checker_linux $ARG
											(complex algorithm explicitly, no benchmark, argc == 7)
		shuf -i 0-9999 -n 500 > args.txt ; ./push_swap $(cat args.txt) | wc -l
											(adaptive algorithm by default, no benchmark, argc == 501)
		shuf -i 0-9999 -n 500 > args.txt ; ./push_swap --bench $(cat args.txt) | ./checker_linux $(cat args.txt)
											(adaptive algorithm by default, benchmark output, argc == 502)
		ARG="4 67 3 87 23"; ./push_swap --bench --adaptive $ARG | ./checker_linux $ARG
											(adaptive algorithm explicitly, benchmark output, argc == 8)
		shuf -i 0-9999 -n 500 > args.txt ; ./push_swap --bench $(cat args.txt) 2> bench.txt | ./checker_linux $(cat args.txt)
											(adaptive algorithm by default, benchmark output, argc == 502)

	Notes:
		- values for sorting seem to always be placed after all the selection flags,
			but it is not stated as a rule in the subject
		- the benchmark mode flag seems to always be placed first, before any algorithm
			flag, but again it is not stated as a rule in the subject
		- in the Usage examples they do not send values for sorting as a single string
			argument any more, e.g. like this ./push_swap "4 67 3 87 23". Even the system
			variable ARG="4 67 3 87 23", when called $ARG, will unwrap into multiple arguments
			./push_swap 4 67 3 87 23 and not into a single string ./push_swap "4 67 3 87 23".
			Still, nothing stops them from doing it. Clearly, I need to implement it to support
			the both ways. Here are all the possible styles that we need to support:
				./push_swap 2 1 3
				./push_swap "2 1 3"
				./push_swap --adaptive 2 1 3
				./push_swap --adaptive "2 1 3"
				./push_swap --adaptive 2 1 "3 6 5"
				./push_swap --bench --adaptive 2 1 3
				./push_swap --bench --adaptive "2 1 3"
				./push_swap --bench --adaptive 2 1 "3 6 5"
	
	Implementation steps:
		1. Validate input exists
			if argc <= 1 	— results in exit failure
			if argc == 2 && argv[1] == NULL 	— results in exit failure
		2. Parse arguments
			Iterate over argv from argv[1] till argv[argc - 1] and for each argument do this:
			- if string starts with "-" and is followed by another "-", then parse the rest
				of the string to recognize the flag. If the flag has been fully recognized,
				set the appropriate inner flag. If the flag was not recognized, exit failure.
			- if string does not start with "-", then treat it as a number container. No
				matter if it is a string of multiple values or a single value, just parse
				the string and append every found number to a growing list of numbers.

*/