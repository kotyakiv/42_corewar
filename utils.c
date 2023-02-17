/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:09:16 by ykot              #+#    #+#             */
/*   Updated: 2023/02/17 15:41:47 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static void	reverse_bytes(u_int8_t *bytes, u_int8_t size)
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

u_int8_t	read_byte(int32_t fd)
{
	u_int8_t	ret;
	u_int8_t	buf;

	ret = read(fd, &buf, 1);
	if (!ret)
		exit(0);
	return (buf);
}

void	error(char *er_str)
{
	ft_putstr(er_str);
	exit(1);
}

int32_t	read_int(int32_t fd)
{
	int32_t		nbr;
	u_int8_t	bytes[4];
	u_int8_t	i;
	u_int32_t	pos;

	i = 5;
	while (--i)
		bytes[i] = 0;
	while (i < 4)
		bytes[i++] = read_byte(fd);
	reverse_bytes(bytes, 4);
	i = 0;
	nbr = 0;
	while (i < 4)
	{
		pos = bytes[i];
		pos = pos << (i * 8);
		nbr += pos;
		++i;
	}
	return (nbr);
}

int16_t	read_short(int32_t fd)
{
	int16_t		nbr;
	u_int8_t	bytes[2];
	u_int8_t	i;
	u_int16_t	pos;

	i = 3;
	while (--i)
		bytes[i] = 0;
	while (i < 2)
		bytes[i++] = read_byte(fd);
	reverse_bytes(bytes, 2);
	i = 0;
	nbr = 0;
	while (i < 2)
	{
		pos = bytes[i];
		pos = pos << (i * 8);
		nbr += pos;
		++i;
	}
	return (nbr);
}
