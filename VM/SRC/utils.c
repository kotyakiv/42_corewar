/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 13:14:18 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:57:19 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	bytes_to_int2(const unsigned char *arena, int pos, int n)
{
	int	nbr;
	int	bits;

	if (!arena || n <= 0)
		return (0);
	nbr = 0;
	bits = 0;
	while (--n >= 0)
	{
		nbr += arena[(pos + n) % MEM_SIZE] << bits;
		bits += 8;
	}
	return (nbr);
}

int	t_ind_position(t_carriage *the_car, int oparg_value)
{
	int	idx_mod;
	int	mem_mod;

	if (the_car->opcode == 13 || the_car->opcode == 14 || the_car->opcode == 15)
	{
		if (oparg_value < 0)
		{
			mem_mod = (-oparg_value) % MEM_SIZE;
			if (the_car->position - mem_mod < 0)
				return ((MEM_SIZE + the_car->position - mem_mod) % MEM_SIZE);
			return ((the_car->position - mem_mod) % MEM_SIZE);
		}
		return ((the_car->position + oparg_value) % MEM_SIZE);
	}
	if (oparg_value < 0)
	{
		idx_mod = (-oparg_value) % IDX_MOD;
		if (the_car->position - idx_mod < 0)
			return ((MEM_SIZE + the_car->position - idx_mod) % MEM_SIZE);
		return ((the_car->position - idx_mod) % MEM_SIZE);
	}
	idx_mod = oparg_value % IDX_MOD;
	return ((the_car->position + idx_mod) % MEM_SIZE);
}

void	set_carry(t_carriage *the_car, int value)
{
	if (!value)
		the_car->carry = 1;
	else
		the_car->carry = 0;
}

int	new_position(int car_pos, int relative_pos)
{
	int	new_pos;

	new_pos = car_pos + relative_pos;
	new_pos %= MEM_SIZE;
	if (new_pos < 0)
		new_pos = MEM_SIZE + new_pos;
	return (new_pos);
}

/*
	write_int_to_arena first writes the most significant byte of the @value
	then shifts the integer 24 bits to the right, 
	masks the result with 0xFF to extract only the lowest 8 bits.
*/

void	write_int_to_arena(unsigned char *arena, int ind, uint32_t value)
{
	if (!arena || ind < 0)
		return ;
	arena[ind % MEM_SIZE] = (value >> 24) & 0xFF;
	arena[(ind + 1) % MEM_SIZE] = (value >> 16) & 0xFF;
	arena[(ind + 2) % MEM_SIZE] = (value >> 8) & 0xFF;
	arena[(ind + 3) % MEM_SIZE] = value & 0xFF;
}
