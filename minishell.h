/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:35:44 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <limits.h>
# include <termios.h>
# include <dirent.h>
# define PROMPT "MINISHELL: "
# define EXPORT "declare -x "
# define FILE_RIGHTS 0664
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif
# ifndef DEFAULT_PATH
#  define DEFAULT_PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# endif

typedef enum e_return {
	RETURN_ERROR = -1,
	RETURN_SUCCESS = 0,
	RETURN_FALSE = 1,
	RETURN_TRUE = 2,
	RETURN_EXIT = 3
}			t_return;

typedef enum e_err_handl {
	ERR_NOT_VALID = 255,
	ERR_NUMERIC,
	ERR_TOO_ARG,
	ERR_SYNTAX,
	ERR_CMD_NOT,
	ERR_CD_FOLDER,
	ERR_FD,
	ERR_FILE
}			t_err_handl;

typedef struct s_re {
	char				*direct;
	char				*file;
	struct s_re			*next;
}				t_re;

typedef struct s_fd {
	int					in;
	int					out;
	int					err;
}				t_fd;

typedef struct s_command {
	int					pid;
	int					errnum;
	t_return			result;
	char				*cmd;
	struct s_envp		*argv;
	struct s_re			*re;
	struct s_fd			*fd;
	struct s_command	*next;
}				t_command;

typedef struct s_envp {
	char				*var;
	struct s_envp		*next;
}				t_envp;

typedef struct s_data {
	struct s_envp		*envp;
	struct s_command	*c_line;
	char				*r_line;
	int					errnum;
	char				*pwd;
	struct sigaction	response;
	struct sigaction	child;
}				t_data;

typedef struct s_parse {
	int					i;
	int					start;
	int					i_string;
	struct s_envp		*str;
}				t_parse;

typedef struct s_parser {
	char				*tmp;
	char				*token;
	struct s_command	*cmd;
	int					len;
	int					inside_echo;
	int					result;
}				t_parser;

void		ft_set_parent_interactive(void);
void		ft_set_parent_active(void);
void		ft_set_parent_heredoc(void);
void		ft_set_child_active(void);
char		*ft_skip_whitespaces(const char *s);
char		*ft_realloc(char *s1, char *s2, int free_s1, int free_s2);
size_t		ft_strlen(const char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memset(void *s, int c, size_t n);
size_t		ft_copy(char *dst, char *src, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_string_dup(const char *s);
char		*ft_get_substring(char const *s, size_t start, size_t len);
t_envp		*ft_lstnew(char *content);
t_envp		*ft_lstlast(t_envp *lst);
void		ft_lstadd_back(t_envp **lst, t_envp *new);
void		ft_delete_list(t_envp **lst);
t_envp		*copy_envp(char **envp);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
size_t		ft_get_int_len(long n, int sign);
char		*ft_int_to_string(long n);
char		*ft_get_var(char *s);
int			ft_str_var_cmp(char *var_name, char *var_elem);
t_envp		*ft_get_envp_element(t_envp *lst, char *var);
void		ft_change_envp(t_data *data, char *var);
void		init(t_data *data, char **envp);
t_command	*ft_create_cmd_elem(void);
void		ft_init_parser(t_parser *parser, t_data *data);
void		ft_check_quote(char c, int *d_quote, int *s_quote);
int			ft_find_end_of_token(char *s, int *inside_echo);
int			ft_end_of_token(char *s, int *inside_echo);
t_re		*ft_lstnew_re(char *direct, char *file);
t_re		*ft_lstlast_re(t_re *lst);
void		ft_lstadd_back_re(t_re **lst, t_re *new);
void		ft_lstdel_re(t_re **re);
void		ft_get_re(t_data *data, t_parser *parser);
int			ft_check_cmd(t_data *data, t_parser *parser);
void		ft_inside_d_quote(t_parse *check, char *input, t_data *data);
void		ft_inside_s_quote(t_parse *check, char *input);
int			ft_check_validity(char *argv);
char		*ft_getenv(char *var, t_envp *envp_list);
void		ft_write_fd(int fd, char *s);
void		ft_write_fd_nl(int fd, char *s);
void		ft_parent_interactive_sigint(int sign);
void		ft_parent_active_sigint(int sign);
void		ft_parent_active_sigquit(int sign);
void		ft_found_dollar(t_parse *check, char *input, t_data *data);
char		*ft_prepare_output(t_envp *list);
char		*ft_get_next_token(t_parser *parser, t_data *data);
char		*ft_check_quotes_insert_var(t_parser *par, t_data *data);
char		*ft_char_in_str(const char *s, const char c);
int			ft_last_pos_in_string(char *s, char c);
void		ft_get_filter_path(char *input, char **path, char **filter);
t_envp		*ft_get_files(char *path);
size_t		ft_words_in_str(char const *s, const char c);
//static void	ft_create_substrings(char const *s, const char c, char **array);
char		**ft_split(char const *s, const char c);
size_t		ft_count_of_in_str(const char *s, const char c);
char		*ft_remove_char(char *s, char c);
char		*ft_found_hash(char *input);
void		ft_add_string(t_parse *check, char *input);
char		*ft_check_dollar_in_heredoc(char *token, t_data *data);
void		ft_questionmark(t_parse *check, t_data *data);
t_return	ft_check_for_asterisk(t_parser *parser, char *input);
void		ft_free_char_array(char **array);
int			ft_pos_in_string(char *s, char c);
void		ft_swap(t_envp **first, t_envp *swap_a);
void		ft_sort_list(t_envp **envp);
char		*ft_strnstr(const char *big, const char *little, size_t len);
t_return	ft_check_element(t_envp *list, char **filter, int len, int size);
t_envp		*ft_apply_filter(t_envp *in_list, char **filter);
size_t		ft_replace_in_string(char *s, char c_replace, char c_with);
char		**ft_get_filter(char *filter);
t_envp		*ft_prepare_list(char *input);
int			ft_wildcard(t_command *cmd, char *input);
void		ft_parser_add_argv(t_data *data, t_parser *parser);
void		ft_free(void *ptr);
int			ft_len_whitespaces(const char *s);
void		ft_inside_echo(t_parser *parser);
void		ft_parser(t_data *data);
int			ft_redirect_prepare_in_in(t_data *data, \
t_command *cmd, char *end_term);
t_return	ft_do_valid_redirections(t_data *data);
void		ft_do_redirections(t_command *cmd, t_re *re);
t_return	ft_redirect_(t_command *cmd, t_re *re, \
t_return (*redirect)(t_command *, t_re *));
int			ft_check_next_token(t_command *cmd, char *file);
t_return	ft_redirect_in_in(t_data *data, t_command *cmd, char *end_term);
int			ft_print_error(t_command *cmd, int errnum, char *token);
void		ft_err_file_cmd(t_command *cmd);
void		ft_err_file(t_command *cmd);
void		ft_err_syntax(t_command *cmd, char *token);
void		ft_err_not_valid(t_command *cmd, char *token);
void		ft_err_numeric(t_command *cmd, char *token);
void		ft_err_too_arg(t_command *cmd);
void		ft_err_cd_folder(t_command *cmd, char *token);
void		ft_err_fd(t_command *cmd, char *token);
void		ft_err_else(t_command *cmd, int errnum);
int			ft_heredoc(t_data *data, int fd_out, char *end_term);
char		*ft_get_next_line(int fd);
int			ft_cycle_cmd(t_data *data);
int			ft_create_pipe(t_command *cmd);
int			ft_build_in_exe(t_command *cmd, t_data *data);
int			ft_exit(t_command *cmd, t_data *data);
int			ft_is_number_only(char *input);
int			ft_count_of_envp(t_envp *envp);
long		ft_string_to_int(const char *nptr);
int			ft_pwd(t_data *data, t_command *cmd);
int			ft_env(t_data *data, t_command *cmd);
void		ft_var_printing(t_data *data);
t_envp		*ft_copy_envp_list(t_envp *envp);
void		ft_add_quotes(t_envp *envp);
int			ft_export(t_data *data, t_command *cmd);
void		ft_delete_envp_elem(t_envp **first, t_envp *to_del);
int			ft_unset(t_data *data, t_command *cmd);
int			ft_cd(t_data *data, t_command *cmd);
int			ft_echo(t_command *cmd);
int			ft_valid_option(char *input);
int			ft_error_codes(t_command *cmd);
int			ft_do_execve(t_command *cmd, t_data *data);
char		*ft_check_path(char *cmd, char **paths);
void		ft_child_process(t_command *cmd, t_data *data, char *cmd_path);
int			ft_connect_pipe(t_command *cmd);
void		ft_close_child_fd(t_command *cmd, t_data *data);
int			ft_close_pipe(t_command *cmd);
char		**ft_create_argv_array(t_command *cmd);
char		**ft_create_envp_array(t_envp *envp);
void		ft_delete_cmd(t_command **commands);
t_command	*ft_last_cmd(t_command *cmd);
void		ft_wait_for_kids(t_data *data);
t_return	ft_redirect_in(t_command *cmd, t_re *re);
t_return	ft_redirect_out_out(t_command *cmd, t_re *re);
t_return	ft_redirect_out(t_command *cmd, t_re *re);
void		ft_clear_mem(t_data *data);
int			ft_check_heredoc_end_term(char *s);

#endif