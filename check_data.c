/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:46:24 by ykot              #+#    #+#             */
/*   Updated: 2023/02/14 17:13:27 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/* 
** iterate through all instructions and check for labels if they exist
** if yes add position in bytes to arg data where it is situated
 */
static char	*check_label(t_data *data)
{
	t_label		*hash_label;
	t_op_data	*op;
	t_list		*iter;
	u_int8_t	i;

	iter = data->op_data;
	while (iter)
	{
		op = (t_op_data *)iter->content;
		i = 0;
		while (i < 3)
		{
			if (op->args[i].label != NULL)
			{
				hash_label = (t_label *)ft_hash_get(data->hashmap, \
											op->args[i].label);
				if (hash_label == NULL)
					return (op->args[i].label);
				op->args[i].data = hash_label->posbytes - op->args[i].data;
			}
			++i;
		}
		iter = iter->next;
	}
	return (FALSE);
}

static t_bool	empty_op_label(t_data *data)
{
	u_int32_t	i;

	if (data->op_data)
		return (FALSE);
	i = 0;
	while (i < HASH)
	{
		if (data->hashmap[i] != NULL)
			return (FALSE);
		++i;
	}
	return (TRUE);
}

void	check_data(t_data *data)
{
	char	*label;

	label = NULL;
	if (data->flags.continue_read)
		error(MISSING_CLOSING_QUOTE, data, NOPOS);
	if (!data->flags.name && !data->flags.comment)
		error(MISSING_NAME_COMMENT, data, NOPOS);
	if (!data->flags.name)
		error(MISSING_NAME, data, NOPOS);
	if (!data->flags.comment)
		error(MISSING_COMMENT, data, NOPOS);
	if (empty_op_label(data))
		error(NO_DATA, data, NOPOS);
	label = check_label(data);
	if (label)
		error_label(LABEL_DOESNT_EXIST, label, data);
}
