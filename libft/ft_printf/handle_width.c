/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:39:30 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_padding(t_opts *opts, char *str, uintmax_t len, int neg)
{
	if (opts->hash == TRUE && *str != '0')
	{
		if (opts->spec == 'x' || opts->spec == 'X')
			return (opts->width - len - 2);
		if (opts->spec == 'o')
			return (opts->width - len - 1);
	}
	if (opts->plus == TRUE || neg == TRUE || opts->space == TRUE)
		return (opts->width - len - 1);
	if (opts->spec == 'p')
		return (opts->width - len - 2);
	return (opts->width - len);
}

int	handle_width(t_opts *opts, char *str, int negative)
{
	int	ret;
	int	len;
	int	pad_size;

	ret = 0;
	len = ft_strlen(str);
	pad_size = calc_padding(opts, str, len, negative);
	if (opts->zero == FALSE && opts->dash == FALSE)
		ret = putchar_nbyte(' ', pad_size);
	ret += handle_flags(opts, str, negative);
	if (opts->zero == TRUE)
		ret = ret + putchar_nbyte('0', pad_size);
	if (opts->dash == TRUE)
		return (ret + putstr_nbyte(str, len) + putchar_nbyte(' ', pad_size));
	return (ret + putstr_nbyte(str, len));
}
