/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_func_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 22:43:52 by jknotts          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * compare symbols in envp and maybe tokens
 */
int	ft_str_var_cmp(char *var_name, char *var_elem)
{
	int	i;

	i = 0;
	while (var_name[i])
	{
		if (var_name[i] != var_elem[i])
			return (0);
		i++;
	}
	if (var_elem[i] == '=' || var_elem[i] == '\0')
		return (1);
	return (0);
}

/*
 * copy environment list
 */
t_envp	*copy_envp(char **envp)
{
	t_envp	*output;
	int		i;

	output = ft_lstnew(envp[0]);
	i = 1;
	while (envp[i])
	{
		ft_lstadd_back(&output, ft_lstnew(envp[i]));
		i++;
	}
	return (output);
}

/*
 * finds node by key
 */
t_envp	*ft_get_envp_element(t_envp *lst, char *var)
{
	t_envp	*tmp;
	char	*var_name;

	tmp = lst;
	while (tmp)
	{
		var_name = ft_get_var(var);
		if (ft_str_var_cmp(var_name, tmp->var))
		{
			free((void *) var_name);
			return (tmp);
		}
		if (var_name)
			free((void *) var_name);
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 * changes envp
 */
void	ft_change_envp(t_data *data, char *var)
{
	t_envp	*tmp;

	tmp = ft_get_envp_element(data->envp, var);
	if (tmp)
	{
		free((void *) tmp->var);
		tmp->var = ft_string_dup(var);
	}
	else
		ft_lstadd_back(&data->envp, ft_lstnew(var));
}

/*
 * return environment variable
 */
char	*ft_getenv(char *var, t_envp *envp_list)
{
	while (!ft_str_var_cmp(var, envp_list->var))
	{
		envp_list = envp_list->next;
		if (envp_list == NULL)
			return (NULL);
	}
	return (&envp_list->var[ft_pos_in_string(envp_list->var, '=') + 1]);
}
