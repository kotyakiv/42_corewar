/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:09:16 by ykot              #+#    #+#             */
/*   Updated: 2023/02/16 23:22:08 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	reverse_bytes(u_int8_t *bytes, u_int8_t size)
{
	u_int8_t	temp;
	u_int8_t	index;
	u_int8_t	mid_position;

	index = 0;
	mid_position = size / 2;
	while (size > mid_position)
	{
		size--;
		temp = bytes[index];
		bytes[index] = bytes[size];
		bytes[size] = temp;
		index++;
	}
}

void	error(char *er_str)
{
	ft_putstr(er_str);
	exit(1);
}
