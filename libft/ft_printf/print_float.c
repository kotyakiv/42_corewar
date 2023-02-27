/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:46:49 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	get_mantissa_zeroes(t_opts *opts, long double nb_dbl)
{
	int			zeroes;
	long double	nb_dec;

	nb_dec = nb_dbl - (uintmax_t)nb_dbl;
	if (opts->dot == FALSE)
		opts->prec = 6;
	zeroes = 0;
	while (nb_dec < 0.1 && zeroes < opts->prec)
	{
		nb_dec *= 10.0;
		zeroes++;
	}
	if (opts->prec == zeroes)
		(zeroes)--;
	if (opts->prec < zeroes)
		zeroes = opts->prec;
	return (zeroes);
}

static char	*join_and_free_str(char *dst, char *str)
{
	char	*temp;

	temp = dst;
	dst = ft_strjoin(dst, str);
	ft_strdel(&temp);
	return (dst);
}

static char	*join_float_str(t_opts *opts, long double nb_dbl, int zeroes)
{
	char		*str_dec;
	char		*str_float;
	int			i;
	long double	nb_dec;

	nb_dec = round_to_prec(opts, &nb_dbl);
	str_float = ft_itoa_base((uintmax_t)nb_dbl, 10);
	if (!(opts->prec == 0 && opts->dot == TRUE))
		str_float = join_and_free_str(str_float, ".");
	if (zeroes > 0)
	{
		i = 0;
		while (i < zeroes)
		{
			str_float = join_and_free_str(str_float, "0");
			i++;
		}
	}
	if (opts->prec > zeroes && opts->prec != 0)
	{
		str_dec = ft_itoa_base((uintmax_t)nb_dec, 10);
		str_float = join_and_free_str(str_float, str_dec);
		ft_strdel(&str_dec);
	}
	return (str_float);
}

static int	handle_float(t_opts *opts, char *str_float, int negative)
{
	int	len;
	int	ret;

	ret = 0;
	len = ft_strlen(str_float);
	if (opts->width > len)
		ret = handle_width(opts, str_float, negative);
	else
		ret = handle_plus_space_hash(opts, str_float, negative);
	ft_strdel(&str_float);
	return (ret);
}

int	print_float(t_opts *opts, va_list ap)
{
	long double	nb_dbl;
	int			negative;
	int			zeroes;
	char		*str;

	if (opts->len[0] == 'L')
		nb_dbl = va_arg(ap, long double);
	else
		nb_dbl = va_arg(ap, double);
	nb_dbl = abs_value(nb_dbl, &negative);
	zeroes = get_mantissa_zeroes(opts, nb_dbl);
	str = join_float_str(opts, nb_dbl, zeroes);
	return (handle_float(opts, str, negative));
}
