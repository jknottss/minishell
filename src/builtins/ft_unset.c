/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 22:43:52 by jknotts          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

int	ft_unset(t_data *data, t_command *cmd)
{
	t_envp	*tmp;
	t_envp	*argv_tmp;

	argv_tmp = cmd->argv;
	while (argv_tmp)
	{
		if (!ft_check_validity(argv_tmp->var))
		{
			ft_print_error(cmd, ERR_NOT_VALID, argv_tmp->var);
		}
		else if (cmd == data->c_line)
		{
			tmp = ft_get_envp_element(data->envp, argv_tmp->var);
			if (tmp)
				ft_delete_envp_elem(&data->envp, tmp);
		}
		argv_tmp = argv_tmp->next;
	}
	return (RETURN_SUCCESS);
}

void	ft_delete_envp_elem(t_envp **first, t_envp *to_del)
{
	t_envp	*tmp;

	if (!first || !to_del)
		return ;
	tmp = *first;
	while (tmp && tmp != to_del && tmp->next != to_del)
		tmp = tmp->next;
	free((void *) to_del->var);
	if (*first == to_del)
		*first = to_del->next;
	else
		tmp->next = to_del->next;
	free((void *) to_del);
}
