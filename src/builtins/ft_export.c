/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 22:43:52 by jknotts          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	ft_export(t_data *data, t_command *cmd)
{
	t_envp	*tmp;

	if (!cmd->argv)
		ft_var_printing(data);
	tmp = cmd->argv;
	while (tmp)
	{
		if (!ft_check_validity(tmp->var))
		{
			ft_print_error(cmd, ERR_NOT_VALID, tmp->var);
		}
		else if (cmd == data->c_line)
			ft_change_envp(data, tmp->var);
		tmp = tmp->next;
	}
	return (RETURN_SUCCESS);
}

/*
 * check string valid
 */
int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	if ((argv[0] >= '0' && argv[0] <= '9') || argv[0] == '=')
		return (0);
	while (argv[i] && argv[i] != '=')
	{
		if ((argv[i] < 'A' || argv[i] > 'Z')
			&& (argv[i] < 'a' || argv[i] > 'z')
			&& (argv[i] < '0' || argv[i] > '9')
			&& argv[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_var_printing(t_data *data)
{
	t_envp	*tmp;
	t_envp	*copy;

	copy = ft_copy_envp_list(data->envp);
	ft_add_quotes(copy);
	ft_sort_list(&copy);
	tmp = copy;
	while (tmp)
	{
		ft_write_fd(data->c_line->fd->out, EXPORT);
		ft_write_fd_nl(data->c_line->fd->out, tmp->var);
		tmp = tmp->next;
	}
	ft_delete_list(&copy);
}

t_envp	*ft_copy_envp_list(t_envp *envp)
{
	t_envp	*output;
	t_envp	*tmp;

	output = (ft_lstnew(envp->var));
	tmp = envp->next;
	while (tmp)
	{
		ft_lstadd_back(&output, ft_lstnew(tmp->var));
		tmp = tmp->next;
	}
	return (output);
}

void	ft_add_quotes(t_envp *envp)
{
	t_envp	*tmp;
	char	*new_value;
	int		len;

	tmp = envp;
	while (tmp)
	{
		len = (ft_pos_in_string(tmp->var, '='));
		if (len == (int) ft_strlen(tmp->var))
			len = 0;
		if (len > 0)
		{
			new_value = (char *) malloc(ft_strlen(tmp->var) + 3);
			len++;
			ft_copy(new_value, tmp->var, len + 1);
			ft_copy(&new_value[len], "\"", 0);
			ft_copy(&new_value[len + 1], &tmp->var[len], 0);
			len = ft_strlen(new_value);
			ft_copy(&new_value[len], "\"", 0);
			free((void *) tmp->var);
			tmp->var = new_value;
		}
		tmp = tmp->next;
	}
}
