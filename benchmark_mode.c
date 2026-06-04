/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   benchmark_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roaleksa <roaleksa@student.42roma.it>      #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026-06-03 18:22:25 by roaleksa          #+#    #+#             */
/*   Updated: 2026-06-03 18:22:25 by roaleksa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	benchmark_mode(t_node *a, t_node *b)
{
	(void)a;
	(void)b;
	write(1, "\n\nBENCHMARK MODE HAS BEEN TRIGERRED\n\n", 37);
}
