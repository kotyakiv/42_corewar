/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   parse_args.c	   :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: bkandemi <bkandemi@student.hive.fi>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2022/11/10 15:08:31 by bkandemi	  #+#	#+#	 */
/*   Updated: 2023/02/03 10:20:22 by bkandemi	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "corewar.h"

static void	get_filename(char **argv, t_vm *vm, int i)
{
	char	*filename;

	filename = ft_strstr(argv[i], ".cor");
	if (filename[4] != '\0')
		error_exit("Wrong file name", vm);
	vm->args.filenames[vm->args.player_count] = ft_strdup(argv[i]);
	if (vm->args.filenames[vm->args.player_count] == NULL)
		error_exit("Memory allocation", vm);
	vm->args.player_count++;
	if (vm->args.player_count > MAX_PLAYERS)
		error_exit("More than 4 players", vm);
}

static void	get_n_option(char **argv, t_vm *vm, int *i)
{
	int	champ_num;

	(*i)++;
	if (ft_isint(argv[*i]))
	{
		champ_num = ft_atoi(argv[*i]);
		if (!(champ_num > 0 && champ_num < 5))
			error_exit(USAGE, vm);
		vm->args.numbers[vm->args.player_count] = champ_num;
		(*i)++;
		if (argv[*i] != NULL && ft_strstr(argv[*i], ".cor") != NULL)
			get_filename(argv, vm, *i);
		else
			error_exit("Wrong file name", vm);
	}
	else
		error_exit("no int after -n flag", vm);
}

/*
	* If there is -l flag it prints memory 64 octets per line
	* Else, it prints 32 octets per line
*/
static void	get_dump_option(char **argv, t_vm *vm, int *i)
{
	(*i)++;
	if (!ft_isint(argv[*i]))
		error_exit("Dump cycle is not an integer", vm);
	vm->args.dump_cycle = ft_atoi(argv[*i]);
	if (vm->args.dump_cycle < 0)
		error_exit("Invalid cycle number", vm);
	vm->args.dump_flag = TRUE;
	vm->args.row_len = 32;
	if (ft_strequ(argv[*i + 1], "-l"))
	{
		vm->args.row_len = 64;
		(*i)++;
	}
}

static void	get_verbose_option(char **argv, t_vm *vm, int *i)
{
	(*i)++;
	if (!ft_isint(argv[*i]))
		error_exit("verbosity option is not an integer", vm);
	vm->args.verbose = ft_atoi(argv[*i]);
	if (vm->args.verbose < 0)
		error_exit("Invalid verbosity option", vm);
}

void	get_args(int argc, char **argv, t_vm *vm)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (i == 1 && ft_strequ(argv[i], "-dump"))
			get_dump_option(argv, vm, &i);
		else if (ft_strequ(argv[i], "-v"))
			get_verbose_option(argv, vm, &i);
		else if (ft_strequ(argv[i], "-n"))
			get_n_option(argv, vm, &i);
		else if (ft_strstr(argv[i], ".cor") != NULL)
			get_filename(argv, vm, i);
		else
			error_exit(USAGE, vm);
	i++;
	}
}
