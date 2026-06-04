/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions_handling.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:32:45 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:32:45 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	i = 0;
	if (argv == NULL || *argv == NULL)
		return ;
	while (argv[i])
		free(argv[i++]);
	free(argv);
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

void	free_and_exit(t_node **a, char **argv)
{
	free_stack_mem(a);
	free_argv_mem(argv);
	write(2, "Error\n", 6);
	exit(EXIT_FAILURE);
}
