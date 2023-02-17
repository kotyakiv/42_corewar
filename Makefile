# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/18 15:34:47 by ykot              #+#    #+#              #
#    Updated: 2023/02/16 22:36:03 by ykot             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = disasm

C_FILES =	check_input_file.c \
			main.c \
			utils.c \
			

O_FILES = $(C_FILES:.c \=.o)

CC = gcc

CFLAGS = #-Wall -Werror -Wextra

all : $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@$(CC) $(CFLAGS) $(C_FILES) libft/libft.a -o $(NAME)
	@make -C libft/ clean

debug:
	@gcc -g -o disasm $(C_FILES) libft/*.c libft/ft_printf/*.c


clean:
	@make -C libft/ clean
fclean: clean
	rm -f $(NAME)

re:	fclean all
