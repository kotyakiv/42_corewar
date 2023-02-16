/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:00:51 by ykot              #+#    #+#             */
/*   Updated: 2023/02/02 15:03:26 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_data(t_data *data)
{
	ft_bzero(data, sizeof(t_data));
	data->hashmap = (t_list **)ft_memalloc(HASH * sizeof(t_list *));
	if (data->hashmap == NULL)
		error(MALLOC_FAILED, NULL, NOPOS);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (check_input_file(argc, argv))
		return (0);
	init_data(&data);
	parsing(&data, argv[1]);
	check_data(&data);
	assemble(&data, argv[1]);
	free_data(&data);
	return (0);
}
