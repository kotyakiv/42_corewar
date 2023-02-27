/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 19:49:24 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	calc_width_asterix(t_opts *opts, int width)
{
	if (width < 0)
	{
		opts->dash = TRUE;
		opts->zero = FALSE;
		return (-width);
	}
	return (width);
}

int	gather_width(t_opts *opts, va_list ap)
{
	int		i;
	long	width;

	i = 0;
	while (is_char_in_str(opts->str[i], FLAGS) == TRUE && opts->str[i] != '\0')
		i++;
	if (opts->str[i] == '*')
	{
		width = va_arg(ap, int);
		if (ft_isdigit(opts->str[i + 1]) == TRUE)
			i++;
		else
			return (calc_width_asterix(opts, width));
	}
	width = 0;
	while (opts->str[i] != '\0' && ft_isdigit(opts->str[i]) == TRUE)
	{
		width = width * 10 + opts->str[i] - '0';
		if (width > 2147483644)
			return (-1);
		i++;
	}
	if (opts->width < 0)
		opts->zero = FALSE;
	return (width);
}
