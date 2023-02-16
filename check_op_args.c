/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_op_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 10:21:23 by ykot              #+#    #+#             */
/*   Updated: 2023/01/31 16:13:41 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static t_bool	is_reg(t_data *data, const char *str)
{
	int32_t		nbr;

	if (*str != 'r')
		return (FALSE);
	if (is_nbr(str + 1))
	{
		nbr = ft_atoi(str + 1);
		if (nbr <= 0)
			error(REGISTER_TOO_SMALL, data, POS);
		if (nbr > REG_NUMBER)
			error(REGISTER_TOO_BIG, data, POS);
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	is_ind(const char *str)
{
	u_int32_t	i;

	if (is_nbr(str))
		return (TRUE);
	if (*str == LABEL_CHAR)
	{
		i = 1;
		while (is_char_in_str(str[i], LABEL_CHARS))
			i++;
		return (TRUE);
	}
	return (FALSE);
}

static t_bool	is_dir(const char *str)
{
	return (*str == DIRECT_CHAR && is_ind(str + 1));
}

int8_t	check_op_args(t_data *data, const char *line)
{
	if (is_reg(data, line))
		return (T_REG);
	if (is_dir(line))
		return (T_DIR);
	if (is_ind(line))
		return (T_IND);
	return (0);
}
