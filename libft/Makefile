# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mafranco <mafranco@student.42barcelona.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/05 17:45:19 by mafranco          #+#    #+#              #
#    Updated: 2024/02/21 01:10:23 by mafranco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIB = libft.h

SRC = ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_itoa.c ft_lstadd_back.c ft_lstadd_front.c \
	ft_lstclear.c ft_lstdelone.c ft_lstlast.c ft_lstnew.c ft_lstsize.c \
	ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
	ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c \
	ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c \
	ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c \
	ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c \
	ft_toupper.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

OBJ	=	$(SRC:.c=.o)

CC	=	cc

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror -I.

SRC_DIR =	src/

GREEN	= \033[1;32m
YELLOW	= \033[1;33m
RESET	= \033[0m


all: $(NAME) 

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIB)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(GREEN)libft.a compiled$(RESET)"

clean:
	@$(RM) -r *.o
	@echo "$(YELLOW)objects of LIBFT removed$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(YELLOW)archive LIBFT removed$(RESET)"

re:	fclean all

.PHONY:	all clean fclean re
