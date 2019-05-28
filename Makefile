# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gfielder <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/24 21:16:21 by gfielder          #+#    #+#              #
#    Updated: 2019/05/01 03:17:20 by gfielder         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=minishell
SRC=src/input.c src/builtin.c src/run.c src/parse.c src/env.c \
	src/expansion.c src/utils.c src/env_aux.c src/bi_cd.c \
	src/bi_env.c src/bi_exit.c src/bi_source.c
SRC_MAIN=src/main.c
INC=-I inc -I lib/libft/inc
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIB=-L lib/libft -lft -ltermcap -lreadline
DEPEND=lib/libft/libft.a 

all: $(NAME)

$(NAME): $(SRC) $(SRC_MAIN) $(DEPEND)
	@$(CC) $(CFLAGS) -o $(NAME) $(INC) $(LIB) $(SRC) $(SRC_MAIN)

clean:
	@make -C lib/libft/ clean


fclean:
	@rm -f $(NAME)
	@make -C lib/libft/ fclean

re:
	@make fclean
	@make all

lib/libft/libft.a:
	@make -C lib/libft

