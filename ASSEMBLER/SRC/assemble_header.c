/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble_header.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:11:29 by ykot              #+#    #+#             */
/*   Updated: 2023/01/27 14:13:55 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	champion_name_comment(t_data *data, int16_t fd, t_bool is_name)
{
	u_int32_t	len;
	u_int32_t	i;

	if (is_name)
		len = ft_strlen(data->header.prog_name);
	else
		len = ft_strlen(data->header.comment);
	i = 0;
	if (is_name)
	{	
		while (i < len)
			write_to_asm(fd, data->header.prog_name[i++], 1);
		write_null_asm(fd, PROG_NAME_LENGTH - len);
		return ;
	}
	while (i < len)
		write_to_asm(fd, data->header.comment[i++], 1);
	write_null_asm(fd, COMMENT_LENGTH - len);
}

void	assemble_header(t_data *data, int16_t fd)
{
	write_nbr_asm(data, fd, COREWAR_EXEC_MAGIC, 4);
	champion_name_comment(data, fd, 1);
	write_null_asm(fd, 4);
	write_nbr_asm(data, fd, data->byte_pass, 4);
	champion_name_comment(data, fd, 0);
	write_null_asm(fd, 4);
}
