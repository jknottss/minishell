#include "../../minishell.h"

int	ft_env(t_data *data, t_command *cmd)
{
	t_envp	*tmp;

	tmp = data->envp;
	while (tmp)
	{
		if (ft_char_in_str(tmp->var, '='))
			ft_write_fd_nl(cmd->fd->out, tmp->var);
		tmp = tmp->next;
	}
	return (RETURN_SUCCESS);
}
