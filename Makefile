# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dlitran <dlitran@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/16 19:22:34 by mafranco          #+#    #+#              #
#    Updated: 2024/04/03 17:05:06 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=	src/minishell.c src/ft_getenv.c src/error_manager.c \
		src/free_data.c src/check_quotes.c src/ft_parse_input.c \
		src/utils.c src/check_pipe.c src/utils_parse.c \
		src/ft_no_pipe.c src/ft_with_pipe.c src/utils_execution.c\
		src/ft_find_funcion.c src/ft_cd.c src/ft_dollar_sign.c \
		src/ft_echo.c src/ft_env.c src/ft_execve.c src/ft_exit.c \
		src/ft_export.c src/ft_pwd.c src/ft_unset.c src/ft_exec_pipe.c\
		src/ft_signal.c src/check_redir.c src/parse_quotes.c \
		src/ft_substr_minishell.c src/ft_dollar_in_quotes.c \
		src/utils_substr.c src/dlr_err.c src/utils_cd.c \
		src/ft_check_path.c src/ft_with_pipe2.c src/ft_no_pipe2.c \
		src/utils_export.c src/check_access.c src/utils_execution2.c \
		src/utils_cd2.c src/manage_inf2.c src/ft_check_path_ex.c \
		src/utils_execve.c src/utils_export2.c src/utils_env.c \
		src/ft_pre_reorganize.c


OBJS = ${SRC:.c=.o}
NAME = minishell

HEADER = inc/header.h
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
LINKING_FLAGS = -lreadline -lhistory -L${HOME}/.brew/opt/readline/lib
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
#LINKING_FLAGS = -lreadline -lhistory -L/usr/local/opt/readline/lib
#COMFILE_FLAGS = -I/usr/local/opt/readline/include
LIBFT_PATH = ./libft

%.o: %.c ${HEADER}
	${CC} ${CFLAGS} $(COMFILE_FLAGS) -I ${HEADER} -c $< -o $@

all:
	@make -C $(LIBFT_PATH)
	@make ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} $(COMFILE_FLAGS) ${LINKING_FLAGS} ${OBJS} -o ${NAME} -L./libft -lft -lncurses

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re:			fclean all

.PHONY: all clean fclean re
