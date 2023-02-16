/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarinstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:45:59 by ykot              #+#    #+#             */
/*   Updated: 2022/11/18 16:50:43 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_char_in_str(char c, const char *str)
{
	int	i;
	int	found;

	found = FALSE;
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
		{
			found = TRUE;
			break ;
		}
		i++;
	}
	return (found);
}
