/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 14:42:38 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/28 10:08:49 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_digits(uintmax_t nb, int base)
{
	unsigned int	digits;

	digits = 0;
	if (nb <= 0)
	{
		nb = -nb;
		digits++;
	}
	while (nb)
	{
		nb = nb / base;
		digits++;
	}
	return (digits);
}

char	*ft_itoa_base(uintmax_t nb, int base)
{
	char			*str;
	unsigned int	size;
	const char		*base_ref;

	base_ref = "0123456789abcdef";
	if (base < 2 || base > 16)
		return (NULL);
	size = count_digits(nb, base);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	str[size] = '\0';
	while (nb > 0)
	{
		str[size - 1] = base_ref[nb % base];
		nb = nb / base;
		size--;
	}
	return (str);
}
