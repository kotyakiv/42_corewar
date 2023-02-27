/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dis_opcode.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 12:40:42 by ykot              #+#    #+#             */
/*   Updated: 2023/02/18 13:07:33 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static void	read_write_arg(int32_t fd, u_int8_t code[3], int8_t dir_size, \
								u_int8_t i)
{
	u_int8_t	buf;
	int32_t		nbr;

	if (code[i] == 1)
	{
		buf = read_byte(fd);
		write_reg(buf);
	}
	if (code[i] == 2)
	{
		if (dir_size == 2)
			nbr = (int32_t) read_short(fd);
		else
			nbr = read_int(fd);
		write_dir(nbr);
	}
	if (code[i] == 3)
	{
		nbr = (int32_t)read_short(fd);
		write_ind(nbr);
	}
}

static void	write_codes(int32_t fd, u_int8_t code[3], int8_t dir_size)
{
	u_int8_t	i;

	i = 0;
	while (i < 3)
	{
		if (code[i] == 0)
			break ;
		if (i == 0)
			ft_putchar(' ');
		else
		{
			ft_putchar(SEPARATOR_CHAR);
			ft_putchar(' ');
		}
		read_write_arg(fd, code, dir_size, i);
		++i;
	}
	ft_putendl("");
}

static void	write_notypecode(int32_t fd, int8_t dir_size)
{
	int32_t		nbr;

	ft_putchar(' ');
	if (dir_size == 2)
		nbr = (int32_t)read_short(fd);
	else
		nbr = read_int(fd);
	write_dir(nbr);
	ft_putendl("");
}

static void	read_write_opcode(int32_t fd, u_int8_t octet)
{
	u_int8_t	buf;
	u_int8_t	code[3];
	int8_t		dir_size;

	if (octet == 0)
		buf = read_byte(fd);
	else
		buf = octet;
	if (buf < 1 || buf > 16)
		error("Wrong opcode");
	dir_size = g_optab[buf - 1].dir_size;
	ft_printf("%s", g_optab[buf - 1].name);
	if (g_optab[buf - 1].typecode)
	{
		read_codes(fd, code);
		write_codes(fd, code, dir_size);
	}
	else
		write_notypecode(fd, dir_size);
}

void	disasm_opcode(int32_t fd, u_int8_t octet)
{
	read_write_opcode(fd, octet);
	while (TRUE)
		read_write_opcode(fd, 0);
}
