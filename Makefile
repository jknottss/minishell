#valgrind --leak-check=full --show-leak-kinds=all --ignore-fn=readline ./minishell
#valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes

NAME		:=	minishell

OBJ_FOLDER	:=	objs
SRC_FOLDER	:=	src

CC			:=	cc
HEADERFILE	:=	minishell.h

SRCS		:=	builtins/ft_cd.c \
                builtins/ft_echo.c \
                builtins/ft_env.c \
                builtins/ft_exit.c \
                builtins/ft_export.c \
                builtins/ft_pwd.c \
                builtins/ft_unset.c \
                env/ft_env_func_a.c \
                env/ft_env_func_b.c \
                env/ft_env_func_c.c \
                error/error_func_a.c \
                error/error_func_b.c \
                error/error_func_c.c \
                exec/ft_exec_a.c \
                exec/ft_exec_b.c \
                exec/ft_heredoc.c \
                exec/ft_pipe.c \
                exec/ft_redirect_a.c \
                exec/ft_redirect_b.c \
                exec/ft_redirect_c.c \
                minishell.c \
                parser/ft_parse_a.c \
                parser/ft_parse_b.c \
                parser/ft_parse_c.c \
                parser/ft_parse_d.c \
                parser/ft_parse_f.c \
                parser/ft_wildcard_a.c \
                signals/ft_signals_a.c \
                signals/ft_signals_b.c \
                utils/ft_get_next_line.c \
                utils/ft_utils_a.c \
                utils/ft_utils_b.c \
                utils/ft_utils_c.c \
                utils/ft_utils_d.c \
                utils/ft_utils_e.c \
                utils/ft_utils_f.c \


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