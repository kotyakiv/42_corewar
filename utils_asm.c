/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:57:04 by ykot              #+#    #+#             */
/*   Updated: 2023/02/02 15:51:52 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_to_asm(int16_t fd, int32_t num, u_int32_t bytes)
{
	write(fd, &num, bytes);
}

void	write_null_asm(int16_t fd, u_int32_t bytes)
{
	u_int8_t	zero;
	u_int32_t	i;

	zero = 0;
	i = 0;
	while (i++ < bytes)
		write(fd, &zero, 1);
}

void	write_nbr_asm(t_data *data, int16_t fd, int32_t nbr, u_int32_t bytes)
{	
	u_int8_t	*num;
	u_int32_t	i;

	num = (u_int8_t *)safe_malloc(data, bytes);
	if (nbr < 0)
	{
		nbr *= -1;
		nbr = ~nbr + 1;
	}
	i = 0;
	while (i < bytes)
	{
		num[i] = nbr >> 8 * i;
		++i;
	}
	while (bytes)
	{
		if (num[bytes - 1] == 0)
			write_null_asm(fd, 1);
		else
			write_to_asm(fd, num[bytes - 1], 1);
		--bytes;
	}
	free(num);
}

u_int8_t	arg_type(t_op_data *op_data)
{
	u_int16_t	type_num;
	u_int8_t	part[3];

	part[0] = op_data->args[0].type_arg << 6;
	part[1] = op_data->args[1].type_arg << 4;
	part[2] = op_data->args[2].type_arg << 2;
	type_num = part[0] + part[1] + part[2];
	return (type_num);
}
