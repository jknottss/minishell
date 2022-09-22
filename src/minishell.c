#include "../minishell.h"

/*
 * Inits data, calling envp copier,
 * sets default path if path not exits,
 * writes PWD env var,
 * sets SHELL env var
 */
void	init(t_data *data, char **envp)
{
	char	*output;
	t_envp	*tmp_envp;

	data->c_line = NULL;
	data->r_line = NULL;
	data->errnum = 0;
	data->envp = copy_envp(envp);
	tmp_envp = ft_get_envp_element(data->envp, "PATH");
	if (!tmp_envp)
		ft_change_envp(data, DEFAULT_PATH);
	tmp_envp = ft_get_envp_element(data->envp, "PWD");
	if (!tmp_envp)
	{
		output = (char *) malloc(BUFFER_SIZE);
		if (!output)
			return ;
		getcwd(output, BUFFER_SIZE);
		output = ft_realloc("PWD=", output, 0, 1);
		ft_change_envp(data, output);
		data->pwd = output;
	}
	else
		data->pwd = ft_string_dup(tmp_envp->var);
	ft_change_envp(data, "SHELL=/42-21/minishell");
}

//todo: maybe we don't need this
//char	*ft_found_hash(char *input)
//{
//	input[0] = '\0';
//	return (NULL);
//}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	(void) argv;
	init(&data, envp);
	ft_set_parent_interactive();
	while (1)
	{
		data.r_line = readline(PROMPT);
		if (data.r_line == 0)
			break ;
		if (ft_strlen(data.r_line) > 0)
			add_history(data.r_line);
		ft_parser(&data);
	}
//	ft_clear_mem(&data);
	return (data.errnum);
}
