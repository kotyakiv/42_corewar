/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:01:51 by ykot              #+#    #+#             */
/*   Updated: 2023/02/02 15:08:31 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void	change_types_to_code(t_op_data *op_data)
{
	u_int8_t	i;

	i = 0;
	while (i < 3)
	{
		if (op_data->args[i].type_arg == T_REG)
			op_data->args[i].type_arg = REG_CODE;
		if (op_data->args[i].type_arg == T_DIR)
			op_data->args[i].type_arg = DIR_CODE;
		if (op_data->args[i].type_arg == T_IND)
			op_data->args[i].type_arg = IND_CODE;
		++i;
	}
}

static void	op_name(t_data *data, char **line, t_op_data *temp_op)
{
	temp_op->num_op = is_op(*line);
	move_ptr(data, line, ft_strlen(g_optab[temp_op->num_op - 1].name));
}

static void	add_op_to_list(t_data *data, t_op_data *temp_op)
{
	t_list	*new_list;

	new_list = (t_list *)ft_lstnewptr(temp_op);
	if (new_list == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	ft_lstappend(&data->op_data, new_list);
}

static char	*str_for_tokens(t_data *data, char *line)
{
	u_int32_t	i;
	char		*str;

	i = 0;
	while (line[i] && line[i] != '#')
	{
		if (line[i] == SEPARATOR_CHAR)
			data->flags.sep++;
		++i;
	}
	str = ft_strsub(line, 0, i);
	if (str == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	return (str);
}

void	tokenization(t_data *data, char *line)
{
	t_op_data	*temp_op;
	char		*str;

	temp_op = (t_op_data *)safe_malloc(data, sizeof(t_op_data));
	op_name(data, &line, temp_op);
	str = str_for_tokens(data, line);
	data->tokens = ft_strsplit(str, SEPARATOR_CHAR);
	if (data->tokens == NULL)
		error(MALLOC_FAILED, data, NOPOS);
	read_tokens(data, data->tokens, temp_op);
	data->byte_pass += bytes_for_op(temp_op);
	change_types_to_code(temp_op);
	ft_strdel(&str);
	data->flags.sep = 0;
	free_split(&data->tokens);
	add_op_to_list(data, temp_op);
}
