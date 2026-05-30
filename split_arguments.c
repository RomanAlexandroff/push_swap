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

/*
 *	Extracts a single word from a string and puts it into
 *	its individual string - one word per function call,
 *	just like get_next_line, but for words. Uses SPACE
 *	character as delimeter. Returns a string with only
 *	"\0" when a string has no more words in it. The caller
 *	shall take care of freeing the memory of such a string.
*/
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
	if (i == 0)
		chr = 0;
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
		i = 0;
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
 *	Takes one single string with multiple values
 *	inside and splits all the values into their
 *	individual strings. Adds NULL at the end of
 *	the array for easier future parsing. Returns a
 *	NULL-terminated array of \0-terminated strings.
*/
char	**split_arguments(char **argv, int argc)
{
	int		args_count;
	char	**output;
	int		i;
	int		j;

	args_count = find_arguments(argv, argc);
	if (!args_count)
		exit(EXIT_FAILURE);
	output = malloc(sizeof(char *) * (args_count + 1));		// allocate memory for the array of pointers to strings
	if (!output)
		return (NULL);
	i = 0;
	j = 0;
	while (i < args_count)
	{
		output[i] = next_word(argv[j]);
		if (!output[i])
			return (NULL);
		if (output[i][0] == '\0')			// if next_word() did not find more words in a current string, then...
		{
			j++;								// move to the next string inside argv
			free(output[i]);					// free the empty string memory
			continue ;							// skip incrementing [i] because we did not get any new argument this iteration 
		}
		i++;
	}
	output[i] = NULL;
	return (output);
}
