/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 18:47:41 by ykot              #+#    #+#             */
/*   Updated: 2023/02/19 12:32:54 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_bool	is_label(char *line)
{
	u_int32_t	i;

	i = 0;
	while (is_char_in_str(line[i], LABEL_CHARS))
		i++;
	if (line[i] != LABEL_CHAR)
		return (FALSE);
	if (is_op(line) != ISNOTOP)
	{
		if (line[i + 1] == ' ' || line[i + 1] == '\t')
			return (TRUE);
		return (FALSE);
	}
	return (TRUE);
}

static t_bool	is_dup(t_data *data, t_label *new_label)
{
	t_label	*temp;

	temp = NULL;
	temp = (t_label *)ft_hash_get(data->hashmap, new_label->name);
	if (temp)
		return (TRUE);
	return (FALSE);
}

static void	label_to_data(t_data *data, t_label *new_label)
{
	t_list		*new_lst;

	new_lst = ft_lstnew_pointer(new_label);
	if (new_lst == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	ft_lstadd(&data->labels, new_lst);
	if (ft_hash_set(data->hashmap, new_label->name, new_label) == 0)
		error(MALLOC_FAILED, data, NOPOS);
}

static void	del_lab(t_label	*new_label)
{
	ft_strdel(&new_label->name);
	free(new_label);
}

void	parse_label(t_data *data, char *line)
{
	u_int32_t	i;
	t_label		*new_label;
	char		*temp;

	temp = line;
	i = 0;
	while (is_char_in_str(*(temp + i), LABEL_CHARS))
		i++;
	new_label = safe_malloc(data, sizeof(t_label));
	new_label->name = ft_strsub(temp, 0, i);
	if (new_label->name == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	if (!is_dup(data, new_label))
	{
		new_label->posbytes = data->byte_pass;
		label_to_data(data, new_label);
	}
	else
		del_lab(new_label);
	move_ptr(data, &temp, i + 1);
	ignore_whitespaces(data, &temp);
	if (is_op(temp) != ISNOTOP)
		tokenization(data, temp);
	else if (*temp != '\0' && *temp != COMMENT_CHAR)
		error(WRONG_INPUT, data, POS);
}
