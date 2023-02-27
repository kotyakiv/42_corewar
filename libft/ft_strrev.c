/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:14:42 by ykot              #+#    #+#             */
/*   Updated: 2022/03/15 12:15:09 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char *str)
{
	int		i;
	int		l;
	char	temp;

	l = ft_strlen(str);
	i = 0;
	while (i < l / 2)
	{
		temp = str[i];
		str[i] = str[l - i - 1];
		str[l - i - 1] = temp;
		++i;
	}
}
