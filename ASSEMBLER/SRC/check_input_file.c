/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:02:58 by ykot              #+#    #+#             */
/*   Updated: 2023/01/31 11:20:03 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* input file isn't .s format */
static u_int8_t	wrong_format(const char *str)
{
	u_int32_t	len;

	len = ft_strlen(str);
	return (!(len >= 3 && str[len - 1] == 's' && str[len - 2] == '.'));
}

u_int8_t	check_input_file(int argc, char **argv)
{
	if (argc == 1)
	{
		ft_putendl(USAGE);
		return (1);
	}
	if (argc > 2)
		error(TOO_MANY_ARGS, NULL, NOPOS);
	if (wrong_format(argv[1]))
		error(WRONG_FORMAT, NULL, NOPOS);
	return (0);
}
