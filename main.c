/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:07:55 by ykot              #+#    #+#             */
/*   Updated: 2023/02/17 00:03:31 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

u_int8_t	read_byte(int32_t fd)
{
	u_int8_t	ret;
	u_int8_t	buf;
	
	ret = read(fd, &buf, 1);
	if (!ret)
		exit(0);
	return (buf);
}

void disasm_header(int32_t fd, u_int8_t *octet)
{
	u_int32_t	ret;
	u_int8_t	buf;
	u_int32_t	i;
	u_int8_t	magic_nbr[4];

	ret = read(fd, &magic_nbr, 4);
	if (ret < 4)
		error("Magic number is short");
	ft_putstr("# magic exec number: ");
	i = 0;
	while (i < 4)
		ft_printf("%02x", magic_nbr[i++]);
	ft_printf("\n%s \"", ".name");
	buf = 1;
	while (buf)
		buf = read_byte(fd);
	ft_printf("\"\n%s \"", ".comment");
	while (!buf)
		buf = read_byte(fd);
	while (buf)
	{
		buf = read_byte(fd);
		write(1, &buf, 1);
	}
	ft_printf("\"\n\n");
	while (!buf)
		buf = read_byte(fd);
}

void	read_codes(u_int8_t code[3], u_int8_t octet)
{
	code[0] = 0b11000000 & octet >> 6;
	code[1] = 0b00110000 & octet >> 4;
	code[2] = 0b00001100 & octet >> 2;
	if (0b00000011 & octet)
		error("wrong arg type");
}

void	write_reg(u_int8_t reg)
{
	ft_printf("r%u ", reg);
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

int32_t	read_nbr(int32_t fd, u_int8_t size)
{
	int32_t		nbr;
	u_int8_t	bytes[4];
	u_int8_t	i;

	i = 5;
	while (--i)
		bytes[i] = 0;
	while (i < size)
		bytes[i++] = read_byte(fd);
	
}

void	write_codes(int32_t fd, u_int8_t code[3])
{
	u_int8_t	buf;
	u_int8_t	i;
	int32_t		nbr;

	i = 0;
	while (i < 3)
	{
		if (code[i] == 1)
		{
			buf = read_byte(fd);
			write_reg(buf);
		}
		if (code[i] == 3)
		{
			nbr	= read_nbr(fd, 2);
			write_reg(buf);
		}
			
	}
	
}

void	disasm_opcode(int32_t fd, u_int8_t octet)
{
	u_int8_t	ret;
	u_int8_t	buf;
	u_int8_t	i;
	u_int8_t	op;
	u_int8_t	op_bytes;
	u_int8_t	code[3];
	
	buf = octet;
	ft_printf("%s ", g_optab[buf - 1].name);
	while (TRUE)
	{
		buf = read_byte(fd);
		ft_printf("%s ", g_optab[buf - 1].name);
		buf = read_byte(fd);
		if (g_optab[buf - 1].typecode)
			read_codes(code, buf);
		write_codes(fd, code);
	}
}

void	read_file(char *argv)
{
	int32_t 	fd;
	u_int8_t	buf;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error("Fail to open file");
	disasm_header(fd, &buf);
	disasm_opcode(fd, buf);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input_file(argc, argv))
		return (0);
	ft_bzero(&data, sizeof(data));
	read_file(argv[1]);
	return (0);
}
