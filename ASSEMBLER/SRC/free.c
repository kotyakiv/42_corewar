/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 12:04:59 by ykot              #+#    #+#             */
/*   Updated: 2023/01/31 16:15:11 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	del_op_data(void *content, size_t size)
{
	u_int8_t	i;
	t_op_data	*op_data;

	i = 0;
	op_data = (t_op_data *)content;
	while (i < 3)
	{
		if (op_data->args[i].label)
			ft_strdel(&op_data->args[i].label);
		++i;
	}
	free(content);
	size++;
}

static void	del(void *content, size_t size)
{
	if (content)
		ft_memdel(&content);
	size++;
}

static void	del_label(void *content, size_t size)
{
	t_label	*label;

	if (content)
	{
		label = (t_label *)content;
		ft_strdel(&label->name);
	}
	free(content);
	size++;
}

void	free_split(char ***str)
{
	size_t	i;

	i = 0;
	if (!str || !*str)
		return ;
	while ((*str)[i])
	{
		ft_strdel(&((*str)[i]));
		i++;
	}
	ft_memdel((void *)str);
}

void	free_data(t_data *data)
{
	free_split(&data->tokens);
	ft_lstdel(&data->op_data, del_op_data);
	ft_lstdel(&data->labels, del_label);
	ft_hash_free(data->hashmap, del);
}
