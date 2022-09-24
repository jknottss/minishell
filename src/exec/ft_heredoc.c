#include "../../minishell.h"

/*
 * exec heredoc func
 */
int	ft_heredoc(t_data *data, int fd_out, char *end_term)
{
	char	*user_input;
	char	*tmp;

	tmp = ft_realloc(end_term, "\n", 0, 0);
	while (1)
	{
		ft_write_fd(STDOUT_FILENO, "> ");
		user_input = ft_get_next_line(STDIN_FILENO);
		if (!user_input)
		{
			free((void *) tmp);
			close(fd_out);
			return (RETURN_ERROR);
		}
		user_input = ft_check_dollar_in_heredoc(user_input, data);
		if (ft_strcmp(user_input, tmp))
			break ;
		ft_write_fd(fd_out, user_input);
		free((void *) user_input);
	}
	free((void *) tmp);
	free((void *) user_input);
	close(fd_out);
	return (RETURN_SUCCESS);
}
