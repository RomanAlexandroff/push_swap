/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-03-13 13:32:53 by roaleksa          #+#    #+#             */
/*   Updated: 2026-03-13 13:32:53 by roaleksa         ###   ########.fr       */
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

static int	find_words(char *str)
{
	int		word_count;
	bool	word_detected;
    int     i;

	word_count = 0;
    i = 0;
	while (str[i])
	{
		word_detected = false;
		while (str[i] == ' ' && str[i])
			i++;
		while (str[i] != ' ' && str[i])
		{
			if (!word_detected)
			{
				word_count++;
				word_detected = true;
			}
			i++;
		}
	}
	return (word_count);
}

char	**extract_values(char *user_input)
{
	int		word_count;
	char	**values;
	int		i;

	i = 0;
	word_count = find_words(user_input);
	if (!word_count)
		exit(EXIT_FAILURE);
	values = malloc(sizeof(char *) * (word_count + 2));
	if (!values)
		return (NULL);
	while (word_count-- >= 0)
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
