/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msgs_asm.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykot <ykot@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:31:34 by mde-maul          #+#    #+#             */
/*   Updated: 2023/02/14 16:50:26 by ykot             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MSGS_ASM_H
# define ERROR_MSGS_ASM_H

# define USAGE "Usage: ./asm file.s"

# define TOO_MANY_ARGS "More than one argument"

# define WRONG_FORMAT "The file isn't .s format"

# define MALLOC_FAILED "Memory allocation"

# define NO_NEW_LINE "No new line at the end of file"

# define CANT_OPEN_FILE "Can't open the file"

# define MISSING_CLOSING_QUOTE "Missing closing \""

# define MISSING_QUOTE "Expect \""

# define MISSING_NAME_COMMENT "Missing name and comment"

# define MISSING_NAME "Missing name"

# define MISSING_COMMENT "Missing comment"

# define NO_DATA "No data"

# define LABEL_DOESNT_EXIST "Label doesn't exist"

# define REGISTER_TOO_SMALL "Register is less than 1"

# define REGISTER_TOO_BIG "Register number is bigger than REG_NUMBER"

# define NAME_TOO_LONG "Name is too long"

# define COMMENT_TOO_LONG "Comment is too long"

# define NAME_ALREADY_EXISTS "Name already exists"

# define COMMENT_ALREADY_EXISTS "Comment already exists"

# define STILL_NO_NAME "There is still no name"

# define STILL_NO_COMMENT "There is still no comment"

# define WRONG_INPUT "Wrong input"

# define WRONG_ARG_TYPE "Wrong argument type"

# define WRONG_NB_OF_ARGS "Wrong number of arguments for op"

# define EXTRA_CHARS "Extra characters"

# define GNL_FAILED "Fail to read the line"

# define EMP_ARG "Empty argument"

#endif
