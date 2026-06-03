/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-05-30 08:11:42 by roaleksa          #+#    #+#             */
/*   Updated: 2026-05-30 08:11:42 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
 *	Checks if two given strings are absolutely
 *	identical to each other. Returns True if
 *	the strings perfectly match, otherwise
 *	returns False.
*/
static bool	strings_equal(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (false);
		i++;
	}
	return (true);
}

/*
 *	Checks if the flag in the given string
 *	is absolutely correct. Returns True if
 *	the flag is perfectly correct. Returns
 *	False if there is any mistake at all.
*/
static bool	validate_flag(const char *str)
{
	return (
		strings_equal(str, "--simple")
		|| strings_equal(str, "--medium")
		|| strings_equal(str, "--complex")
		|| strings_equal(str, "--adaptive")
		|| strings_equal(str, "--bench")
	);
}

/*
 *	Sets flag variables to their default values,
 *	detects flags among the arguments inside argv,
 *	checks if the detected flags are fully correct, 
 *	changes flag variables values according to the
 *	detected and validated flags. Returns False if
 *	there is any issue with the detected flags,
 *	otherwise returns True.
 *	The function does not limit the number of flags
 *	in argv, meaning that no matter the number of
 *	the complexity flags in the call, the complexity
 *	is always set according to the last flag; no
 *	matter the number of benchmark flags in the call,
 *	1 or 5 or 30, the benchmark will be set to ON.
*/
bool	set_flags(char **argv, t_mode *complexity_mode, bool *bench_flag)
{
	int	i;

	*bench_flag = false;
	*complexity_mode = ADAPTIVE_MODE;
	i = -1;
	while (argv[++i] != NULL)
	{
		if (argv[i][0] != '-' || argv[i][1] != '-')
			continue ;
		if (!validate_flag(argv[i]))
			return (false);
		if (argv[i][2] == 's')
			*complexity_mode = SIMPLE_MODE;
		else if (argv[i][2] == 'm')
			*complexity_mode = MEDIUM_MODE;
		else if (argv[i][2] == 'c')
			*complexity_mode = COMPLEX_MODE;
		else if (argv[i][2] == 'a')
			*complexity_mode = ADAPTIVE_MODE;
		else if (argv[i][2] == 'b')
			*bench_flag = true;
	}
	return (true);
}
