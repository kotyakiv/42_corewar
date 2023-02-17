/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 22:07:55 by ykot              #+#    #+#             */
/*   Updated: 2023/02/17 16:14:27 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

static void	print_magic_code(int32_t fd)
{
	u_int32_t	ret;
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
}

static void	disasm_header(int32_t fd, u_int8_t *octet)
{
	u_int8_t	buf;

	print_magic_code(fd);
	buf = 1;
	while (buf)
	{
		buf = read_byte(fd);
		write(1, &buf, 1);
	}
	ft_printf("\"\n%s \"", ".comment");
	while (!buf)
		buf = read_byte(fd);
	while (buf)
	{
		buf = read_byte(fd);
		if (ft_isascii(buf))
			write(1, &buf, 1);
	}
	ft_printf("\"\n\n");
	while (!buf)
		buf = read_byte(fd);
	*octet = buf;
}

static void	read_file(char *argv)
{
	int32_t		fd;
	u_int8_t	buf;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
		error("Fail to open file");
	disasm_header(fd, &buf);
	disasm_opcode(fd, buf);
}

int	main(int argc, char **argv)
{
	if (check_input_file(argc, argv))
		return (0);
	read_file(argv[1]);
	return (0);
}
