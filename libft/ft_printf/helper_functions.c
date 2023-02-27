/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 11:11:19 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 11:20:33 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putchar_nbyte(char c, int n)
{
	int	i;

	i = 0;
	if (n < 0)
		n = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
	return (n);
}

int	putstr_nbyte(char const *s, int nbyte)
{
	if (nbyte < 0)
		nbyte = 0;
	return (write(1, s, nbyte));
}
