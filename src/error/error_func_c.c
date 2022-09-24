#include "../../minishell.h"

int	ft_error_codes(t_command *cmd)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < 255)
	{
		ft_write_fd(cmd->fd->out, "error code ");
		tmp = ft_int_to_string(i);
		tmp = ft_realloc(tmp, " ", 1, 0);
		ft_write_fd(cmd->fd->out, tmp);
		ft_write_fd_nl(cmd->fd->out, strerror(i));
		i++;
		free((void *) tmp);
	}
	return (RETURN_SUCCESS);
}