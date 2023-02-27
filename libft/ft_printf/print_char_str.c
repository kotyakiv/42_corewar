/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 10:07:09 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	handle_char(t_opts *opts, char c)
{
	if (opts->width < 1)
		return (write(1, &c, 1));
	if (opts->dash == TRUE)
		return (write(1, &c, 1) + putchar_nbyte(' ', opts->width - 1));
	if (opts->zero == TRUE)
		return (putchar_nbyte('0', opts->width - 1) + write(1, &c, 1));
	return (putchar_nbyte(' ', opts->width - 1) + write(1, &c, 1));
}

int	print_char(t_opts *opts, va_list ap)
{
	char	c;

	c = va_arg(ap, int);
	return (handle_char(opts, c));
}

int	print_str(t_opts *opts, va_list ap)
{
	char	*s;
	int		len;

	s = va_arg(ap, char *);
	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (opts->dot == TRUE && opts->prec >= 0 && opts->prec < len)
		len = opts->prec;
	if (opts->width <= len)
		return (putstr_nbyte(s, len));
	if (opts->dash == TRUE)
		return (putstr_nbyte(s, len) + putchar_nbyte(' ', opts->width - len));
	return (putchar_nbyte(' ', opts->width - len) + putstr_nbyte(s, len));
}
