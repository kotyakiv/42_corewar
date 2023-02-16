/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_fn.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 15:26:54 by ykot              #+#    #+#             */
/*   Updated: 2023/02/16 10:17:52 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* Print type of error and exit */
void	error(char *er_str, t_data *data, t_bool is_pos)
{
	ft_putstr_fd("Error", 2);
	if (data != NULL && is_pos)
		ft_printf(" [%d:%d]", data->pos.r, data->pos.c);
	ft_putstr_fd(" - ", 2);
	ft_putendl_fd(er_str, 2);
	if (data)
		free_data(data);
	exit(1);
}

void	error_label(char *er_str, char *label, t_data *data)
{
	ft_putstr_fd("Error", 2);
	ft_putstr_fd(" - ", 2);
	ft_putendl_fd(er_str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(label, 2);	
	if (data)
		free_data(data);
	exit(1);
}
