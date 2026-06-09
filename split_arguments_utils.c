/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:34:58 by ccrucian          #+#    #+#             */
/*   Updated: 2026/06/08 17:24:29 by ccrucian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
 *	individual and common strings.
*/
int	find_arguments(char **argv, int argc)
{
	int		args_count;
	int		j;

	args_count = 0;
	j = 0;
	while (j < argc)
	{
		args_count += count_arguments(argv[j]);
		j++;
	}
	return (args_count);
}
