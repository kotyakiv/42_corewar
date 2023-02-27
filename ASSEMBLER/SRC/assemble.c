/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assemble.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 14:06:05 by ykot              #+#    #+#             */
/*   Updated: 2023/02/16 16:15:24 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* create a new name ending (.s -> .cor) */
static char	*new_prog_name(t_data *data, char *prog_name)
{
	char	*temp;
	char	*new_name;

	temp = ft_strsub(prog_name, 0, ft_strlen(prog_name) - 1);
	if (temp == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	new_name = ft_strjoin(temp, "cor");
	if (new_name == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	ft_strdel(&temp);
	return (new_name);
}

/* change to asm code the instructions with arg */
static void	op_to_assemble(t_data *data, t_op_data *op_data, int16_t fd)
{
	u_int32_t	i;

	write_to_asm(fd, op_data->num_op, 1);
	if (g_optab[op_data->num_op - 1].typecode)
		write_to_asm(fd, arg_type(op_data), 1);
	i = 0;
	while (i < 3)
	{
		if (op_data->args[i].type_arg == 0)
			break ;
		if (op_data->args[i].type_arg == REG_CODE)
			write_to_asm(fd, op_data->args[i].data, 1);
		if (op_data->args[i].type_arg == IND_CODE)
			write_nbr_asm(data, fd, op_data->args[i].data, 2);
		if (op_data->args[i].type_arg == DIR_CODE)
			write_nbr_asm(data, fd, op_data->args[i].data, \
				g_optab[op_data->num_op - 1].dir_size);
		++i;
	}
}

/* go throw list of instructions and write them to assemble code */
static void	assemble_exec_code(t_data *data, int16_t fd)
{
	t_list		*iter;
	t_op_data	*op_data;

	iter = data->op_data;
	while (iter)
	{
		op_data = (t_op_data *)iter->content;
		op_to_assemble(data, op_data, fd);
		iter = iter->next;
	}
}

void	assemble(t_data *data, char *prog_name)
{
	int		fd;
	char	*new_file_name;

	new_file_name = new_prog_name(data, prog_name);
	fd = open(new_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		error(CANT_OPEN_FILE, data, NOPOS);
	ft_printf("Writing output program to %s\n", new_file_name);
	assemble_header(data, fd);
	assemble_exec_code(data, fd);
	ft_strdel(&new_file_name);
	close(fd);
}
