/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 13:37:03 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/28 10:08:37 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long double	abs_value(long double nb_dbl, int *negative)
{
	*negative = 0;
	if (nb_dbl < 0.0)
	{
		nb_dbl = -nb_dbl;
		*negative = 1;
	}
	return (nb_dbl);
}
