/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 12:25:01 by ykot              #+#    #+#             */
/*   Updated: 2023/01/30 16:37:49 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_hash_free(t_list **hashmap, void (*del)(void *, size_t))
{
	size_t	i;

	i = 0;
	while (i < HASH)
	{
		if (hashmap[i])
		{
			ft_lstdel(&hashmap[i], del);
		}
		i++;
	}
	free(hashmap);
}
