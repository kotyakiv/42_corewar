/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:39:08 by ykot              #+#    #+#             */
/*   Updated: 2023/02/17 15:42:16 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

void	write_reg(u_int8_t reg)
{
	ft_printf("r%u", reg);
}

void	write_ind(int32_t nbr)
{
	ft_putnbr(nbr);
}

void	write_dir(int32_t nbr)
{
	ft_putchar('%');
	ft_putnbr(nbr);
}

void	read_codes(int32_t fd, u_int8_t code[3])
{
	u_int8_t	buf;

	buf = read_byte(fd);
	code[0] = (0b11000000 & buf) >> 6;
	code[1] = (0b00110000 & buf) >> 4;
	code[2] = (0b00001100 & buf) >> 2;
	if (0b00000011 & buf)
		error("wrong arg type");
}
