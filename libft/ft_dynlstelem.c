/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dynlstelem.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bkandemi <bkandemi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 00:29:26 by ykot              #+#    #+#             */
/*   Updated: 2023/02/10 14:27:03 by bkandemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_dblist	*sub_dynlstelem(t_dynlist alst, size_t elem, \
								t_dblist *temp, int i)
{
	t_dblist	*iter;

	iter = temp;
	if (alst.size / 2 > elem)
	{
		while (i)
		{
			iter = iter->next;
			i--;
		}
	}
	else
	{
		while (i)
		{
			iter = iter->prev;
			i--;
		}
	}
	return (iter);
}

t_dblist	*ft_dynlstelem(t_dynlist alst, size_t elem)
{
	t_dblist	*temp;
	int			i;

	if (alst.size == 0 || elem > alst.size - 1)
		return (NULL);
	if (alst.size / 2 > elem)
	{
		temp = alst.head;
		i = elem;
	}
	else
	{
		temp = alst.tail;
		i = alst.size - elem - 1;
	}
	temp = sub_dynlstelem(alst, elem, temp, i);
	return (temp);
}
