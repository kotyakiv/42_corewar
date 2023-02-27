/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:02:58 by ykot              #+#    #+#             */
/*   Updated: 2023/02/17 15:49:16 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "disasm.h"

/* input file isn't .cor format */
static u_int8_t	wrong_format(const char *str)
{
	u_int32_t	len;

	len = ft_strlen(str);
	return (!(len >= 5 && !ft_strncmp(str + len - 4, ".cor", 4)));
}

u_int8_t	check_input_file(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putendl("Usage: ./disasm file.cor");
		return (1);
	}
	if (argc > 2)
		error("Too many arguments");
	if (wrong_format(argv[1]))
		error("The file isn't .cor format");
	return (0);
}
