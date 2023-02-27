/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: briffard <briffard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 09:26:01 by bkandemi          #+#    #+#             */
/*   Updated: 2023/02/19 12:58:11 by briffard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"
# include "op.h"
# include "oplist.h"

//# define PROG_NAME_LENGTH		128
//# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3
# define CHAMP_MAX_SIZE		682
# define MAX_PLAYERS		4

# define USAGE	"\nUsage: ./corewar [-dump CYCLE [-l]]\
[-v NUM][[-n NUM] champion1.cor] ...\n\n\
\t-dump CYCLE\t: Dumps memory in hexadecimal format with 32 octets/line and exits\n\
\t-dump CYCLE -l\t: Dumps memory in hexadecimal format with 64 octets/line and exits\n\
\t-n NUM\t\t: Sets the number of the next player\n\
\t-v NUM\t\t: Verbosity levels, add together to enable several\n\
\t\t   1\t: Writes alive player and prints aff\n\
\t\t   2\t: Show cycles\n\
\t\t   4\t: Show operations\n\
\t\t   8\t: Show deaths\n\
\t\t  16\t: Show cursor movements\n"

typedef struct s_args
{
	int		player_count;
	int		numbers[MAX_PLAYERS];
	int		dump_flag;
	int		dump_cycle;
	char	*filenames[MAX_PLAYERS];
	int		row_len;
	int		verbose;
}			t_args;

typedef struct s_champ
{
	int		magic;
	char	name[PROG_NAME_LENGTH];
	char	comment[COMMENT_LENGTH];
	int		code_size;
	char	code[CHAMP_MAX_SIZE];
	int		id;
}			t_champ;

typedef struct s_carriage
{
	int				id;
	int				carry;
	unsigned char	opcode;
	int				last_live;
	int				remaining_cycles;
	int				position;
	int				registers[REG_NUMBER];
	int				last_live_cycle;
}					t_carriage;

typedef struct s_vm
{
	t_args		args;
	t_champ		champs[MAX_PLAYERS];
	t_dynlist	carriages;
	int			winner;
	int			cycles;
	int			cycles_to_die;
	int			checks;
	int			nb_of_live;
	int			last_player_alive;
	int			carriage_count;
	int			the_check_cycle;
}				t_vm;

typedef struct s_op_args
{
	int	types[3];
	int	size[3];
	int	values[3];
	int	arg_count;
	int	size_tdir;
}	t_op_args;

typedef int	(*t_dispacht_op_codes)(t_vm *vm,
									unsigned char *arena,
									t_carriage *the_car);

int		op_live(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_ld(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_st(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_add(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_sub(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_and(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_or(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_xor(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_zjmp(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_ldi(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_sti(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_fork(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_lld(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_lldi(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_lfork(t_vm *vm, unsigned char *arena, t_carriage *the_car);
int		op_aff(t_vm *vm, unsigned char *arena, t_carriage *the_car);

/* get_args */
void	get_args(int argc, char **argv, t_vm *vm);

/* set_player_order */
void	set_player_order(t_vm *vm);

/* read_champs */
void	read_champs(t_vm *vm);

/* place_champs */
void	place_champs(unsigned char *arena, t_vm *vm);

/* init_carriages */
int		add_carriage(t_carriage *carriage, t_dynlist *alst);
void	init_carriages(t_vm *vm);

/* the_cycle */
void	run_carriages(t_vm *vm, unsigned char *arena);
void	check(t_vm *vm);
void	the_cycle(t_vm *vm, unsigned char *arena);

/* print */
void	print_player_order(t_args args);
void	print_carriages(t_vm vm);

/* exit */
void	del_fn(void *content);
void	error_exit(char *err_msg, t_vm *vm);
void	ok_exit(t_vm *vm);

/*check_argument*/

/*utils*/
int		bytes_to_int2(const unsigned char *arena, int pos, int n);
int		new_position(int car_pos, int relative_pos);

void	get_types_size(unsigned char *arena, t_carriage *the_car, \
t_op_args *op_args);
int		get_oparg_values(unsigned char *arena, t_carriage *the_car, \
t_op_args *op_args);
void	write_int_to_arena(unsigned char *arena, int ind, uint32_t value);
int		t_ind_position(t_carriage *the_car, int oparg_value);
void	set_carry(t_carriage *the_car, int value);

#endif
