/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_carriages.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:49:49 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:56:24 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	add_carriage(t_carriage *carriage, t_dynlist *alst)
{
	t_dblist	*new;

	new = ft_dblstnew_pointer(carriage);
	if (!new)
		return (0);
	ft_dynlstadd(alst, new);
	return (1);
}

void	init_carriages(t_vm *vm)
{
	int			i;
	t_carriage	*carriage;

	i = 0;
	while (i < vm->args.player_count)
	{
		carriage = (t_carriage *)ft_memalloc(sizeof(*carriage));
		if (!carriage)
			error_exit("Memory allocation", vm);
		carriage->id = vm->champs[i].id;
		carriage->position = MEM_SIZE / vm->args.player_count * i;
		carriage->registers[0] = -vm->champs[i].id;
		carriage->remaining_cycles = -1;
		carriage->last_live = FALSE;
		if (!add_carriage(carriage, &vm->carriages))
			error_exit("Memory allocation", vm);
		i++;
	}
	i = 1;
	while (i < REG_NUMBER)
	{
		carriage->registers[i] = 0;
		i++;
	}
}
