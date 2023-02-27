/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_types.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 13:55:47 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:11 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	get_first(int byte, t_op_args *op_args)
{
	if ((byte & 0b11000000) == 0b01000000)
	{
		op_args->types[0] = T_REG;
		op_args->size[0] = 1;
	}
	else if ((byte & 0b11000000) == 0b10000000)
	{
		op_args->types[0] = T_DIR;
		op_args->size[0] = op_args->size_tdir;
	}
	else if ((byte & 0b11000000) == 0b11000000)
	{
		op_args->types[0] = T_IND;
		op_args->size[0] = 2;
	}
}

static void	get_second(int byte, t_op_args *op_args)
{
	if ((byte & 0b00110000) == 0b00010000)
	{
		op_args->types[1] = T_REG;
		op_args->size[1] = 1;
	}
	else if ((byte & 0b00110000) == 0b00100000)
	{
		op_args->types[1] = T_DIR;
		op_args->size[1] = op_args->size_tdir;
	}
	else if ((byte & 0b00110000) == 0b00110000)
	{
		op_args->types[1] = T_IND;
		op_args->size[1] = 2;
	}
}

static void	get_third(int byte, t_op_args *op_args)
{
	if ((byte & 0b00001100) == 0b00000100)
	{
		op_args->types[2] = T_REG;
		op_args->size[2] = 1;
	}
	else if ((byte & 0b00001100) == 0b00001000)
	{
		op_args->types[2] = T_DIR;
		op_args->size[2] = op_args->size_tdir;
	}
	else if ((byte & 0b00001100) == 0b00001100)
	{
		op_args->types[2] = T_IND;
		op_args->size[2] = 2;
	}
}

static void	init_op_args(t_op_args *op_args, int opcode)
{
	ft_memset(op_args->types, 0, 3 * sizeof(int));
	ft_memset(op_args->size, 0, 3 * sizeof(int));
	ft_memset(op_args->values, 0, 3 * sizeof(int));
	op_args->arg_count = g_oplist[opcode - 1].arg_cnt;
	op_args->size_tdir = g_oplist[opcode - 1].t_dir_size;
}

void	get_types_size(unsigned char *arena,
					t_carriage *the_car,
					t_op_args *op_args)
{
	int	byte;

	init_op_args(op_args, the_car->opcode);
	byte = arena[(the_car->position + 1) % MEM_SIZE];
	get_first(byte, op_args);
	get_second(byte, op_args);
	get_third(byte, op_args);
}
