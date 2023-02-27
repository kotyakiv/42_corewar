/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gather_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 21:28:55 by bkandemi          #+#    #+#             */
/*   Updated: 2022/03/26 22:41:13 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	gather_specifier(t_opts *opts)
{
	char	*end;
	int		i;

	i = 0;
	end = ft_strchr(opts->str, '\0');
	while (SPECS[i] != '\0')
	{
		if (*(end - 1) == SPECS[i])
			opts->spec = SPECS[i];
		i++;
	}
}

void	gather_flags(t_opts *opts)
{
	int	i;

	i = 0;
	while (opts->str[i] != '\0' && is_char_in_str(opts->str[i], FLAGS) == TRUE)
	{
		if (opts->str[i] == '-')
			opts->dash = TRUE;
		else if (opts->str[i] == '+')
			opts->plus = TRUE;
		else if (opts->str[i] == '#')
			opts->hash = TRUE;
		else if (opts->str[i] == ' ' && opts->plus == FALSE)
			opts->space = TRUE;
		else if (opts->str[i] == '0')
			opts->zero = TRUE;
		i++;
	}
	if (opts->dash == TRUE)
		opts->zero = FALSE;
}

void	gather_len_mod(t_opts *opts, char c)
{
	char	*len_flag;

	len_flag = ft_strchr(opts->str, c);
	if (len_flag != NULL)
	{
		if (*(len_flag + 2) == '\0')
		{
			opts->len[0] = c;
			return ;
		}
		if (*(len_flag + 1) == c && *(len_flag + 3) == '\0')
		{
			opts->len[0] = c;
			opts->len[1] = c;
			return ;
		}
		if (len_flag != NULL && (*(len_flag + 1)) == 'f')
		{
			opts->len[0] = c;
			return ;
		}
	}
}
