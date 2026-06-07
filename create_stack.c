/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/13 13:32:41 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/05 15:24:15 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	add_new_node(t_node **stack, int value, t_bench *bench)
{
	t_node	*new_node;
	t_node	*last_node;

	if (!stack)
		return (0);
	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (0);
	new_node->node_after = NULL;
	new_node->value = value;
	new_node->bench = bench;			// assign pointer to the instance of the bench struct
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
	return (1);
}

static long	ft_atod(const char *str)
{
	long	output;
	int		sign;
	int		i;

	output = 0;
	sign = 1;
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
		output *= 10;
		output += str[i] - '0';
		i++;
	}
	return (sign * output);
}

/*
 *	Can skip strings which start with "--"
 *	in order not to parse flags by accident
*/
void	create_stack_safely(t_node **a, char **argv, t_bench *bench)
{
	long	value;
	int		i;

	value = 0;
	i = -1;
	while (argv[++i] != NULL)
	{
		if (argv[i][0] == '-' && argv[i][1] == '-')
			continue ;
		if (!characters_check(argv[i]))
			free_and_exit(a, argv);
		value = ft_atod(argv[i]);
		if (value < INT_MIN || value > INT_MAX)
			free_and_exit(a, argv);
		if (!duplicates_check(*a, (int)value))
			free_and_exit(a, argv);
		if (!add_new_node(a, (int)value, bench))
			free_and_exit(a, argv);
	}
	free_argv_mem(argv);
}
