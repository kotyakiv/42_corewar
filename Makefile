# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 15:34:47 by ykot              #+#    #+#              #
#    Updated: 2023/02/14 16:24:46 by ykot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

C_FILES =	assemble.c \
			assemble_header.c \
			check_input_file.c \
			check_op_args.c \
			check_data.c \
			read_tokens.c \
			error_fn.c \
			free.c \
			main.c \
			parse_header.c \
			parse_label.c \
			parse_tokens.c \
			parsing.c \
			tokenization.c \
			utils.c \
			utils2.c \
			utils_asm.c \

O_FILES = $(C_FILES:.c \=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(CFLAGS) $(C_FILES) libft/libft.a -o $(NAME)
	@make -C libft/ clean

debug:
	@gcc -g -o asm $(C_FILES) libft/*.c libft/ft_printf/*.c


clean:
	@make -C libft/ clean
fclean: clean
	rm -f $(NAME)

re:	fclean all
