/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:34:58 by roaleksa          #+#    #+#             */
/*   Updated: 2026/05/28 16:21:25 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char	*next_word(char *str)
{
	static int	chr = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (str[chr] == ' ')
		chr++;
	while ((str[chr + len] != ' ') && str[chr + len])
		len++;
	next_word = malloc(sizeof(char) * (len + 1));
	if (!next_word)
		return (NULL);
	while ((str[chr] != ' ') && str[chr])
		next_word[i++] = str[chr++];
	next_word[i] = '\0';
	return (next_word);
}


/*
 *	Counts the number of arguments in an array of strings
 *	no matter if arguments are located in their individual
 *	strings, or in one common string, or in a mix of
 *	individual and common strings.
*/
static int	find_arguments(char **argv, int argc)
{
	int		args_count;
	bool	arg_detected;
	int		i;
	int		j;

	args_count = 0;
	i = 0;
	j = 0;
	while (j < argc)
	{
		while (argv[j][i])
		{
			arg_detected = false;
			while (argv[j][i] == ' ' && argv[j][i])
				i++;
			while (argv[j][i] != ' ' && argv[j][i])
			{
				if (!arg_detected)
				{
					args_count++;
					arg_detected = true;
				}
				i++;
			}
		}
		j++;
	}
	return (args_count);
}

/*
 *	Takes one single string with multiple
 *	values inside and splits all the values
 *	into their individual strings. Returns
 *	as an array of strings
*/
char	**split_arguments(char **argv, int argc)
{
	int		args_count;
	char	**output;
	int		i;

// TO-DO: make the function to work with multiple strings
	i = 0;
	args_count = find_arguments(argv, argc);
	if (!args_count)
		exit(EXIT_FAILURE);
	output = malloc(sizeof(char *) * (args_count + 2));		// allocate memory for the array of pointers to strings
	if (!output)
		return (NULL);
	while (args_count-- >= 0)		// TODO: split here
	{
		if (!i)
		{
			values[i] = malloc(sizeof(char));
			if (values[i] == NULL)
				return (NULL);							// forgot to free everything allocated before
			values[i++][0] = '\0';
			continue ;
		}
		values[i++] = next_word(user_input);
	}
	values[i] = NULL;
	return (values);
}
