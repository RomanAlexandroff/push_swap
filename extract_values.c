#include "push_swap.h"

static char	*next_word(char *input)
{
	static int	chr = 0;
	char		*next_word;
	int			len;
	int			i;

	len = 0;
	i = 0;
	while (input[chr] == ' ')
		chr++;
	while ((input[chr + len] != ' ') && input[chr + len])
		len++;
	next_word = malloc((size_t)len * sizeof(char) + 1);
	if (next_word == NULL)
		return (NULL);
	while ((input[chr] != ' ') && input[chr])
		next_word[i++] = input[chr++];
	next_word[i] = '\0';
	return (next_word);
}

static int	find_words(char *input)
{
	int		word_count;
	bool	word_detected;
    int     i;

	word_count = 0;
    i = 0;
	while (input[i])
	{
		word_detected = false;
		while (input[i] == ' ' && input[i])
			i++;
		while (input[i] != ' ' && input[i])
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

char	**extract_values(char *input)
{
	int		word_count;
	char	**values;
	int		i;

	i = 0;
	word_count = find_words(input);
	if (!word_count)
		exit(1);
	values = malloc(sizeof(char *) * (size_t)(word_count + 2));
	if (values == NULL)
		return (NULL);
	while (word_count-- >= 0)
	{
		if (!i)
		{
			values[i] = malloc(sizeof(char));
			if (values[i] == NULL)
				return (NULL);
			values[i++][0] = '\0';
			continue ;
		}
		values[i++] = next_word(input);
	}
	values[i] = NULL;
	return (values);
}
