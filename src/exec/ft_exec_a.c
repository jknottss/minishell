#include "../../minishell.h"

/*
 * init command element
 */
t_command	*ft_create_cmd_elem(void)
{
	t_command	*output;

	output = (t_command *) malloc(sizeof(t_command));
	if (!output)
		return (NULL);
	ft_memset((void *) output, 0, sizeof(t_command));
	output->fd = (t_fd *) malloc(sizeof(t_fd));
	if (!output->fd)
		return (NULL);
	output->fd->in = STDIN_FILENO;
	output->fd->out = STDOUT_FILENO;
	output->fd->err = STDERR_FILENO;
	output->result = RETURN_FALSE;
	output->re = NULL;
	return (output);
}

/*
 * exec builtins
 */
int	ft_build_in_exe(t_command *cmd, t_data *data)
{
	if (ft_strcmp(cmd->cmd, "exit"))
		return (ft_exit(cmd, data));
	else if (ft_strcmp(cmd->cmd, "pwd"))
		return (ft_pwd(data, cmd));
	else if (ft_strcmp(cmd->cmd, "env"))
		return (ft_env(data, cmd));
	else if (ft_strcmp(cmd->cmd, "export"))
		return (ft_export(data, cmd));
	else if (ft_strcmp(cmd->cmd, "unset"))
		return (ft_unset(data, cmd));
	else if (ft_strcmp(cmd->cmd, "cd"))
		return (ft_cd(data, cmd));
	else if (ft_strcmp(cmd->cmd, "echo"))
		return (ft_echo(cmd));
	else if (ft_strcmp(cmd->cmd, "error_codes"))
		return (ft_error_codes(cmd));
	return (RETURN_FALSE);
}

/*
 * execute commands
 */
int	ft_do_execve(t_command *cmd, t_data *data)
{
	char	**paths;
	char	*cmd_path;

	paths = ft_split(ft_getenv("PATH", data->envp), ':');
	if (!paths)
		return (ft_print_error(cmd, ERR_FILE, NULL));
	cmd_path = ft_check_path(cmd->cmd, paths);
	ft_free_char_array(paths);
	if (!cmd_path)
		return (ft_print_error(cmd, ERR_CMD_NOT, NULL));
	if (cmd->fd->in == RETURN_ERROR)
	{
		free(cmd_path);
		return (1);
	}
	ft_change_envp(data, ft_realloc("_=", cmd_path, 0, 0));
	cmd->pid = fork();
	if (cmd->pid < 0)
		return (ft_print_error(cmd, errno, NULL));
	if (cmd->pid == 0)
		ft_child_process(cmd, data, cmd_path);
	free((void *) cmd_path);
	return (0);
}

char	*ft_check_path(char *cmd, char **paths)
{
	char	*test_path;
	int		i;

	i = 0;
	if (ft_char_in_str(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_string_dup(cmd));
	}
	while (paths && paths[i])
	{
		test_path = ft_realloc(paths[i], "/", 0, 0);
		test_path = ft_realloc(test_path, cmd, 1, 0);
		if (access(test_path, F_OK) == RETURN_SUCCESS)
			return (test_path);
		free((void *) test_path);
		i++;
	}
	return (NULL);
}

void	ft_child_process(t_command *cmd, t_data *data, char *cmd_path)
{
	char	**envp;
	char	**argv;

	ft_set_child_active();
	ft_connect_pipe(cmd);
	ft_close_child_fd(cmd, data);
	envp = ft_create_envp_array(data->envp);
	argv = ft_create_argv_array(cmd);
	if (execve(cmd_path, argv, envp) == RETURN_ERROR)
		ft_print_error(cmd, errno, NULL);
	ft_close_pipe(cmd);
	ft_free_char_array(envp);
	ft_free_char_array(argv);
	ft_delete_list(&data->envp);
	ft_delete_list(&cmd->argv);
	ft_delete_cmd(&data->c_line);
	free((void *) data->pwd);
	free((void *) cmd_path);
	exit(0);
}
