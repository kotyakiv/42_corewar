/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 14:31:19 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 11:18:47 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <wctype.h>
# include <stdint.h>

# define TRUE	1
# define FALSE	0

# define VALID	"-+ #0123456789.hlLcspdiouxXf%*"
# define SPECS	"cspdiouxXf%"
# define INT	"diouxX"
# define UINT	"ouxXp"
# define FLAGS	"-+ #0"

typedef struct s_opts
{
	char	*str;
	int		dash;
	int		plus;
	int		space;
	int		hash;
	int		zero;
	int		width;
	int		dot;
	int		prec;
	char	len[2];
	char	spec;
}			t_opts;

int			ft_printf(const char *format, ...);
int			parse(const char *format, va_list ap);
int			put_format(t_opts *opts, va_list ap);

/* Gather flags and conversion specifier */
void		gather_specifier(t_opts *opts);
void		gather_flags(t_opts *opts);
void		gather_len_mod(t_opts *opts, char c);
int			gather_precision(t_opts *opts, va_list ap);
int			gather_width(t_opts *opts, va_list ap);

/* Handle flags */
int			handle_flags(t_opts *opts, char *str, int negative);
int			handle_plus_space_hash(t_opts *opts, char *str, int negative);
intmax_t	handle_length_mod(t_opts *opts, va_list ap);
intmax_t	handle_unsigned_length_mod(t_opts *opts, va_list ap);
int			handle_width(t_opts *opts, char *str, int negative);
int			handle_precision(t_opts *opts, char *str, int negative);

/* Print %, %c and %s */
int			handle_char(t_opts *opts, char c);
int			print_char(t_opts *opts, va_list ap);
int			print_str(t_opts *opts, va_list ap);

/* Print %d, %i, %u, %o, %x, %X, %p */
int			print_signed_int(t_opts *opts, va_list ap);
int			print_unsigned_int(t_opts *opts, va_list ap);

/* Print %f */
long double	round_to_prec(t_opts *opts, long double *nb_dbl);
int			print_float(t_opts *opts, va_list ap);

/*	Helper functions */
int			putchar_nbyte(char c, int n);
int			putstr_nbyte(char const *s, int nbyte);
// int			is_char_in_str(char c, char *str);

#endif
