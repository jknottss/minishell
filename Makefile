# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkaufman <rkaufman@student.42wolfsburg.de> +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/18 09:14:26 by rkaufman          #+#    #+#              #
#    Updated: 2022/04/11 09:11:39 by rkaufman         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#valgrind --leak-check=full --show-leak-kinds=all --ignore-fn=readline ./minishell
#valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

NAME		:=	minishell

OBJ_FOLDER	:=	objs
SRC_FOLDER	:=	src

CC			:=	cc
HEADERFILE	:=	minishell.h

SRCS		:=	main.c \

OBJS		:= $(SRCS:%.c=$(OBJ_FOLDER)/%.o)

CFLAGS		:=	-Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L/opt/homebrew/Cellar/readline/8.1.2/lib -lreadline -o $(NAME)

$(OBJS): $(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c
	@mkdir -p $(@D)
	$(CC) -c $(CFLAGS) -I/opt/homebrew/Cellar/readline/8.1.2/include -o $@ $<

clean:
	rm -fr $(OBJ_FOLDER)

fclean: clean
	rm -fr $(NAME)

re: fclean all

norm:
	cd srcs && norminette -R CheckForbiddenSourceHeader $(SRCS)
	norminette -R CheckForbiddenSourceHeader $(HEADERFILE)
	
val:
	valgrind --leak-check=full --trace-children=yes --track-fds=yes -s ./minishell

.PHONY: clean fclean re