/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 20:31:07 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	initiate(t_opts *opts)
{
	opts->str = ft_memalloc(1);
	opts->spec = '\0';
	opts->dash = FALSE;
	opts->hash = FALSE;
	opts->plus = FALSE;
	opts->space = FALSE;
	opts->zero = FALSE;
	opts->width = 0;
	opts->dot = FALSE;
	opts->prec = 0;
	ft_bzero(opts->len, 2);
}

static void	realloc_before_append(char **str)
{
	char	*new;

	new = (char *)ft_memalloc(ft_strlen(*str) + 2);
	new = ft_strcpy(new, *str);
	ft_strdel(str);
	*str = new;
}

static void	reset(t_opts *opts)
{
	ft_strdel(&(opts->str));
	initiate(opts);
}

static int	handle_format(const char *format, t_opts *opts, int *i, va_list ap)
{
	int	j;
	int	ret;

	j = 0;
	ret = 0;
	if (format[*i] == '\0')
		return (ret);
	if (is_char_in_str(format[*i], VALID) == FALSE)
	{
		ft_putchar(format[*i]);
		return (ret + 1);
	}
	while (is_char_in_str(format[*i], VALID) == TRUE)
	{
		realloc_before_append(&(opts->str));
		opts->str[j++] = format[*i];
		if (is_char_in_str(format[*i], SPECS) == TRUE)
		{
			ret = put_format(opts, ap);
			reset(opts);
			break ;
		}
		*i = *i + 1;
	}
	return (ret);
}

int	parse(const char *format, va_list ap)
{
	t_opts	opts;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	initiate(&opts);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			i++;
			ret = ret + handle_format(format, &opts, &i, ap);
		}
		else
		{
			ft_putchar(format[i]);
			ret++;
		}
		if (format[i] != '\0')
			i++;
	}
	ft_strdel(&(opts.str));
	return (ret);
}
