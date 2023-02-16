/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 14:07:28 by ykot              #+#    #+#             */
/*   Updated: 2023/02/14 17:13:20 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "libft.h"
# include "op.h"
# include "error_msgs_asm.h"

# define ISNOTOP 17
# define POS 1
# define NOPOS 0

typedef u_int8_t	t_bool;

typedef struct s_op
{
	u_int8_t	num_op;
	char		*name;
	u_int8_t	num_arg;
	t_arg_type	typeofarg[3];
	t_bool		typecode;
	u_int8_t	dir_size;
}				t_op;

typedef struct s_pos
{
	u_int32_t	r;
	u_int32_t	c;
}				t_pos;

typedef struct s_label
{
	char		*name;
	u_int32_t	posbytes;
}				t_label;

typedef struct s_flags
{
	t_bool		continue_read;
	t_bool		name;
	t_bool		comment;
	u_int32_t	read_bytes;
	u_int32_t	sep;
}				t_flags;

typedef struct s_arg
{
	u_int8_t	type_arg;
	int32_t		data;
	char		*label;
}				t_arg;

typedef struct s_op_data
{
	u_int8_t	num_op;
	t_arg		args[3];
}				t_op_data;

typedef struct s_data
{
	t_header	header;
	t_flags		flags;
	t_pos		pos;
	u_int32_t	byte_pass;
	t_list		*labels;
	t_list		*op_data;
	t_list		**hashmap;
	char		**tokens;
}				t_data;

static const t_op	g_optab[17] = {
{1, "live", 1, {T_DIR}, 0, 4},
{2, "ld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
{3, "st", 2, {T_REG, T_IND | T_REG}, 1, 4},
{4, "add", 3, {T_REG, T_REG, T_REG}, 1, 4},
{5, "sub", 3, {T_REG, T_REG, T_REG}, 1, 4},
{6, "and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
{7, "or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
{8, "xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 1, 4},
{9, "zjmp", 1, {T_DIR}, 0, 2},
{10, "ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
{11, "sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 1, 2},
{12, "fork", 1, {T_DIR}, 0, 2},
{13, "lld", 2, {T_DIR | T_IND, T_REG}, 1, 4},
{14, "lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 1, 2},
{15, "lfork", 1, {T_DIR}, 0, 2},
{16, "aff", 1, {T_REG}, 1, 4},
{0, 0, 0, {0}, 0, 0}
};

/* check_input_file */
u_int8_t	check_input_file(int argc, char **argv);

/* parsing */
void		parsing(t_data *data, const char *file_name);

/* parse_header */
void		parse_header(t_data *data, char *line);
void		continue_parse_name(t_data *data, char *line);
void		continue_parse_comment(t_data *data, char *line);

/* parse_label */
t_bool		is_label(char *line);
void		parse_label(t_data *data, char *line);

/* tokenization */
void		tokenization(t_data *data, char *line);

/* read_tokens */
u_int8_t	is_op(char *line);
void		read_tokens(t_data *data, char **tokens, t_op_data *temp_op);
/* check_op_args */
int8_t		check_op_args(t_data *data, const char *line);

/* parse_tokens */
void		parse_token(t_data *data, t_op_data *temp_op, \
				int32_t arg_data, char **line);

/* check_data */
void		check_data(t_data *data);

/* assemble */
void		assemble(t_data *data, char *prog_name);

/* assemvle_header */
void		assemble_header(t_data *data, int16_t fd);

/* utils_asm */
void		write_to_asm(int16_t fd, int32_t num, u_int32_t bytes);
void		write_null_asm(int16_t fd, u_int32_t bytes);
void		write_nbr_asm(t_data *data, int16_t fd, int32_t nbr, \
							u_int32_t bytes);
u_int8_t	arg_type(t_op_data *op_data);

/* utils */
int8_t		check_gnl(t_data *data, int8_t gnl, char **line);
void		ignore_whitespaces(t_data *data, char **str);
u_int8_t	is_empty_line(char *line);
u_int8_t	is_comment_line(char *line);
t_bool		is_nbr(const char *str);

/* utils2 */
void		extra_characters(t_data *data, char *line);
void		move_ptr(t_data *data, char **str, u_int32_t i);
void		*safe_malloc(t_data *data, size_t size);
u_int8_t	bytes_for_op(t_op_data *temp_op);

/* error_fn */
void		error(char *er_str, t_data *data, t_bool is_pos);
void		error_label(char *er_str, char *label, t_data *data);
/* free */
void		free_data(t_data *data);
void		free_split(char ***str);

#endif
