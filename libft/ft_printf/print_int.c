/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:50:25 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_len(t_opts *opts, char *str)
{
	if (*str == '0' && opts->dot == TRUE && opts->prec == 0)
		return (0);
	return (ft_strlen(str));
}

static int	handle_int(t_opts *opts, char *str, int negative)
{
	int	len;
	int	ret;

	len = calc_len(opts, str);
	if (opts->dot == TRUE && opts->prec >= len)
		ret = handle_precision(opts, str, negative);
	else if (opts->width > len)
		ret = handle_width(opts, str, negative);
	else
		ret = handle_plus_space_hash(opts, str, negative);
	ft_strdel(&str);
	return (ret);
}

int	print_signed_int(t_opts *opts, va_list ap)
{
	intmax_t	nb;
	char		*str;
	int			negative;

	nb = handle_length_mod(opts, ap);
	nb = (intmax_t)abs_value((intmax_t)nb, &negative);
	str = ft_itoa_base(nb, 10);
	return (handle_int(opts, str, negative));
}

int	print_unsigned_int(t_opts *opts, va_list ap)
{
	uintmax_t	nb;
	char		*str;
	int			negative;

	nb = handle_unsigned_length_mod(opts, ap);
	if (opts->spec == 'o')
		str = ft_itoa_base(nb, 8);
	else if (opts->spec == 'x' || opts->spec == 'p')
		str = ft_itoa_base(nb, 16);
	else if (opts->spec == 'X')
		str = ft_itoa_base_upper(nb, 16);
	else
		str = ft_itoa_base(nb, 10);
	negative = FALSE;
	opts->plus = FALSE;
	opts->space = FALSE;
	return (handle_int(opts, str, negative));
}
