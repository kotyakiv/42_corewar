# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/19 15:48:43 by mde-maul          #+#    #+#              #
#    Updated: 2023/02/19 19:46:25 by ykot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Virtual Machine
CORE := corewar

INCL_CORE    := -I ./VM/INCLUDES/

CORE_SRC_DIR := ./VM/SRC/
CORE_FILES    := check.c	\
			exit.c	\
			get_arg_types.c	\
			get_args.c	\
			get_oparg_values.c	\
			init_carriages.c	\
			main.c	\
			op_add_sub.c	\
			op_aff.c	\
			op_bitwise.c	\
			op_fork.c	\
			op_ld.c	\
			op_live.c	\
			op_lld.c	\
			op_st.c		\
			op_zjmp.c	\
			place_champs.c	\
			print.c	\
			read_champs.c	\
			run_carriages.c	\
			set_player_order.c	\
			the_cycle.c	\
			utils.c	\

#OBJECTS
CORE_OBJ_DIR := ./VM/OBJ/
CORE_OBJ     := $(addprefix $(CORE_OBJ_DIR), $(CORE_FILES:%.c=%.o))

#ASSEMBLER
ASM    := asm

#INCLUDES
INCL_ASM    := -I ./ASSEMBLER/INCLUDES/

ASM_SRC_DIR := ./ASSEMBLER/SRC/
ASM_FILES    := assemble_header.c	\
				assemble.c			\
				check_data.c 		\
				check_input_file.c	\
				check_op_args.c		\
				error_fn.c			\
				free.c				\
				main.c				\
				parse_header.c		\
				parse_label.c		\
				parse_tokens.c		\
				parsing.c			\
				read_tokens.c		\
				tokenization.c		\
				utils_asm.c			\
				utils.c				\
				utils2.c			\

#OBJECTS
ASM_OBJ_DIR := ./ASSEMBLER/OBJ/
ASM_OBJ     := $(addprefix $(ASM_OBJ_DIR), $(ASM_FILES:%.c=%.o))


#DISASSEMBLER
DISASM    := disasm

#INCLUDES
INCL_DISASM    := -I ./DISASSEMBLER/INCLUDES/

DISASM_SRC_DIR := ./DISASSEMBLER/SRC/
DISASM_FILES    := 	check_input_file.c	\
				dis_opcode.c	\
				main.c	\
				read_write_arg.c \
				utils.c \

#OBJECTS
DISASM_OBJ_DIR := ./DISASSEMBLER/OBJ/
DISASM_OBJ     := $(addprefix $(DISASM_OBJ_DIR), $(DISASM_FILES:%.c=%.o))
	
#COMPILATION
CC      := gcc -g
CFLAGS  := -Wall -Werror -Wextra

#CLEAN & FCLEAN
RM_DIR  := rm -rf
RM      := rm -f

#LIBRAIRIE
LIBFT   	:= libft.a
INCL_LFT    := -I ./libft/
LIB 		:= -L ./libft/ -lft

all: $(ASM) $(CORE) $(DISASM)

$(CORE): $(CORE_OBJ)
	@$(CC) $(CFLAGS) -o $(CORE) $(CORE_OBJ) $(LIB)

$(CORE_OBJ_DIR)%.o:$(CORE_SRC_DIR)%.c
	@make -sC ./libft/
	@mkdir -p $(CORE_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCL_LFT) $(INCL_CORE) -o $@ -c $<



##########################################
$(ASM):  $(ASM_OBJ)
	@$(CC) $(CFLAGS) -o $(ASM) $(ASM_OBJ) $(LIB)

$(ASM_OBJ_DIR)%.o:$(ASM_SRC_DIR)%.c
	@make -sC ./libft/
	@mkdir -p $(ASM_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCL_LFT) $(INCL_ASM) -o $@ -c $<


########################################
$(DISASM): $(DISASM_OBJ)
	@$(CC) $(CFLAGS) -o $(DISASM) $(DISASM_OBJ) $(LIB)

$(DISASM_OBJ_DIR)%.o:$(DISASM_SRC_DIR)%.c
	@make -sC ./libft/
	@mkdir -p $(DISASM_OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCL_LFT) $(INCL_DISASM) -o $@ -c $<

#######################################
$(LIBFT):
	make -sC ./libft/

clean:
	make -sC ./libft/ clean
	$(RM_DIR) $(CORE_OBJ_DIR) $(DISASM_OBJ_DIR) $(ASM_OBJ_DIR)

fclean: clean
	make -sC ./libft/ fclean
	$(RM) $(CORE) $(ASM) $(DISASM)

re: fclean all

.PHONY: all clean fclean re
