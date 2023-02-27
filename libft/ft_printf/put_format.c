/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:54:03 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	gather(t_opts *opts, va_list ap)
{
	gather_specifier(opts);
	if (ft_strlen(opts->str) > 1)
	{
		gather_flags(opts);
		opts->width = gather_width(opts, ap);
		opts->prec = gather_precision(opts, ap);
		gather_len_mod(opts, 'h');
		gather_len_mod(opts, 'l');
		gather_len_mod(opts, 'L');
	}
}

int	put_format(t_opts *opts, va_list ap)
{
	gather(opts, ap);
	if (opts->spec == 'c')
		return (print_char(opts, ap));
	else if (opts->spec == 's')
		return (print_str(opts, ap));
	else if (opts->spec == 'd' || opts->spec == 'i')
		return (print_signed_int(opts, ap));
	else if (is_char_in_str(opts->spec, UINT) == TRUE)
		return (print_unsigned_int(opts, ap));
	else if (opts->spec == 'f')
		return (print_float(opts, ap));
	else if (opts->spec == '%')
		return (handle_char(opts, '%'));
	else
		exit(1);
}
