/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 21:53:15 by ykot              #+#    #+#             */
/*   Updated: 2023/02/16 23:22:17 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISASM_H
# define DISASM_H

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

typedef struct	s_data
{
	u_int8_t	header;
	char 		*str;
	u_int32_t	ptr;
	
}				t_data;

u_int8_t	check_input_file(int argc, char **argv);
void	reverse_bytes(u_int8_t *bytes, u_int8_t size);
void	error(char *er_str);

#endif
