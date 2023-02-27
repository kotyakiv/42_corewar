/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:40:36 by ykot              #+#    #+#             */
/*   Updated: 2023/02/02 15:07:27 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* Check for extra (forbidden) checracters after instructions */
void	extra_characters(t_data *data, char *line)
{
	ignore_whitespaces(data, &line);
	if (*line != '\0' && *line != COMMENT_CHAR)
		error(EXTRA_CHARS, data, POS);
}

void	move_ptr(t_data *data, char **str, u_int32_t i)
{
	while (i-- && **str != '\0')
	{
		(*str)++;
		data->pos.c++;
	}
}

/* allocate memory, init by zero and check allocation */
void	*safe_malloc(t_data *data, size_t size)
{
	void	*mem;

	mem = (void *)malloc(size);
	if (mem == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	ft_bzero(mem, size);
	return (mem);
}

u_int8_t	bytes_for_op(t_op_data *temp_op)
{
	u_int8_t	bytes;
	u_int8_t	i;

	bytes = 1;
	if (g_optab[temp_op->num_op - 1].typecode)
		bytes++;
	i = 0;
	while (i < 3)
	{
		if (temp_op->args[i].type_arg == 0)
			break ;
		if (temp_op->args[i].type_arg == T_REG)
			bytes += 1;
		if (temp_op->args[i].type_arg == T_IND)
			bytes += 2;
		if (temp_op->args[i].type_arg == T_DIR)
			bytes += g_optab[temp_op->num_op - 1].dir_size;
		++i;
	}
	return (bytes);
}
