/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrucian <ccrucian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 13:34:58 by roaleksa          #+#    #+#             */
/*   Updated: 2026/06/10 11:08:35 by ccrucian         ###   ########.fr       */
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

static char	**cleanup_output(char **output, int count)
{
	while (count > 0)
	{
		free(output[count - 1]);
		count--;
	}
	free(output);
	return (NULL);
}

static char	**fill_output(char **output, char **argv, int args_count)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < args_count)
	{
		output[i] = next_word(argv[j]);
		if (!output[i])
			return (cleanup_output(output, i));
		if (output[i][0] == '\0')
		{
			j++;
			free(output[i]);
			continue ;
		}
		i++;
	}
	output[i] = NULL;
	return (output);
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

	args_count = find_arguments(argv, argc);
	if (!args_count)
		exit(EXIT_FAILURE);
	output = malloc(sizeof(char *) * (args_count + 1));
	if (!output)
		return (NULL);
	output = fill_output(output, argv, args_count);
	return (output);
}
