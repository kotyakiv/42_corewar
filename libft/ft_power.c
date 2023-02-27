/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 09:21:17 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/28 10:10:20 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_power(double nb, int power)
{
	double	result;

	result = 1.0;
	if (power == 0)
		return (1.0);
	if (power < 0)
	{
		while (power < 0)
		{
			result = result / nb;
			power++;
		}
		return (result);
	}
	while (power > 0)
	{
		result = result * nb;
		power--;
	}
	return (result);
}
