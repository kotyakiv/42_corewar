/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnewptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 22:49:34 by bkandemi          #+#    #+#             */
/*   Updated: 2023/01/20 23:54:16 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnewptr(void *content)
{
	t_list	*lstnew;

	lstnew = (t_list *)ft_memalloc(sizeof(t_list));
	if (!lstnew)
		return (NULL);
	if (!content)
	{
		lstnew->content = NULL;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	else
	{
		lstnew->content = content;
		lstnew->content_size = 0;
		lstnew->next = NULL;
	}
	return (lstnew);
}
