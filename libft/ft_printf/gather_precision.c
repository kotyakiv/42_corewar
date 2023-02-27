/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:49:45 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_prec(char *dot, va_list ap)
{
	int	precision;
	int	asterisk;
	int	i;

	precision = 0;
	asterisk = 0;
	i = 1;
	while (dot != NULL && dot[i] != '\0' && ft_isdigit(dot[i]) == TRUE)
	{
		precision = precision * 10 + dot[i] - '0';
		if (precision > 2147483646)
		{
			precision = -1;
			break ;
		}
		i++;
	}
	if (dot != NULL && *(dot + 1) == '*')
	{
		asterisk = va_arg(ap, int);
		if (asterisk >= 0)
			return (asterisk);
		return (-1);
	}
	return (precision);
}

int	gather_precision(t_opts *opts, va_list ap)
{
	char	*dot;

	dot = ft_strchr(opts->str, '.');
	if (dot != NULL)
		opts->dot = TRUE;
	opts->prec = calc_prec(dot, ap);
	if (opts->prec >= 0 && opts->dot == TRUE)
		opts->zero = FALSE;
	return (opts->prec);
}
