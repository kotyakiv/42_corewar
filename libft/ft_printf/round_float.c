/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:05:56 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	round_to_prec(t_opts *opts, long double *nb_dbl)
{
	uintmax_t	round_down;
	uintmax_t	round_up;
	long double	nb_dec;

	nb_dec = *nb_dbl - (uintmax_t)(*nb_dbl);
	nb_dec = nb_dec * ft_power(10.0, opts->prec);
	round_down = (uintmax_t)(nb_dec);
	round_up = (uintmax_t)(nb_dec + 1);
	if ((nb_dec - round_down) > (round_up - nb_dec))
	{
		nb_dec = round_up;
		if (opts->prec == 0)
			(*nb_dbl)++;
	}
	else if ((nb_dec - round_down) == (round_up - nb_dec))
	{
		nb_dec = round_up;
		if (opts->prec == 0 && ((uintmax_t)(*nb_dbl + 1)) % 2 == 0)
			(*nb_dbl)++;
	}
	else
		nb_dec = round_down;
	return (nb_dec);
}
