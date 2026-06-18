/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:34:58 by ccrucian          #+#    #+#             */
/*   Updated: 2026/06/10 11:25:21 by ccrucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

int	count_arguments(char *argv)
{
	int			i;
	int			count;
	bool		arg_detected;

	i = 0;
	count = 0;
	while (argv[i])
	{
		arg_detected = false;
		while (argv[i] == ' ' && argv[i])
			i++;
		while (argv[i] != ' ' && argv[i])
		{
			if (!arg_detected)
			{
				arg_detected = true;
				count++;
			}
			i++;
		}
	}
	return (count);
}

/*
 *	Counts the number of arguments in an array of strings
 *	no matter if arguments are located in their individual
 *	strings, or in one common string, or in a mix of
 *	individual and common strings. Outputs Error and exits
 *	if encounters an empty argument.
*/
int	find_arguments(char **argv, int argc)
{
	int		args_count;
	int		j;

	args_count = 0;
	j = 0;
	while (j < argc)
	{
		if (argv[j][0] == '\0')
			free_and_exit(NULL, NULL);
		args_count += count_arguments(argv[j]);
		j++;
	}
	return (args_count);
}
