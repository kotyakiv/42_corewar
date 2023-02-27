/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:36:25 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_len(t_opts *opts, char *str)
{
	if (*str == '0' && opts->dot == TRUE && opts->prec == 0)
	{
		if (opts->hash == TRUE && opts->spec == 'o')
			return (ft_strlen(str));
		return (0);
	}
	return (ft_strlen(str));
}

static int	calc_space_padding(t_opts *opts, char *str, int neg)
{
	if (opts->width > opts->prec)
	{
		if (opts->hash == TRUE && *str != '0')
		{
			if (opts->spec == 'x' || opts->spec == 'X')
				return (opts->width - opts->prec - 2);
		}
		if (opts->plus == TRUE || neg == TRUE || opts->space == TRUE)
			return (opts->width - opts->prec - 1);
		return (opts->width - opts->prec);
	}
	return (0);
}

int	handle_precision(t_opts *opts, char *str, int negative)
{
	int	ret;
	int	len;
	int	space;

	ret = 0;
	len = calc_len(opts, str);
	space = calc_space_padding(opts, str, negative);
	if (opts->dash == FALSE)
	{
		ret += putchar_nbyte(' ', space);
		ret += handle_flags(opts, str, negative);
		ret += putchar_nbyte('0', opts->prec - len);
		ret += putstr_nbyte(str, len);
	}
	else
	{
		ret += handle_flags(opts, str, negative);
		ret += putchar_nbyte('0', opts->prec - len);
		ret += putstr_nbyte(str, len);
		ret += putchar_nbyte(' ', space);
	}
	return (ret);
}
