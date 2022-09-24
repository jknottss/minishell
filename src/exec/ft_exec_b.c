/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:09:27 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

char	**ft_create_argv_array(t_command *cmd)
{
	char	**output;
	t_envp	*tmp;
	int		i;

	output = (char **) malloc((ft_count_of_envp (cmd->argv) + 2) \
	* sizeof(char *));
	if (!output)
		return (NULL);
	tmp = cmd->argv;
	output[0] = ft_string_dup(cmd->cmd);
	i = 1;
	while (tmp)
	{
		output[i] = ft_string_dup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

char	**ft_create_envp_array(t_envp *envp)
{
	char	**output;
	t_envp	*tmp;
	int		i;

	output = (char **) malloc((ft_count_of_envp(envp) + 1) * sizeof(char *));
	if (!output)
		return (NULL);
	tmp = envp;
	i = 0;
	while (tmp)
	{
		output[i] = ft_string_dup(tmp->var);
		tmp = tmp->next;
		i++;
	}
	output[i] = NULL;
	return (output);
}

void	ft_delete_cmd(t_command **commands)
{
	t_command	*tmp;

	while (*commands)
	{
		tmp = *commands;
		*commands = (*commands)->next;
		free((void *) tmp->cmd);
		free((void *) tmp->fd);
		tmp->fd = NULL;
		tmp->cmd = NULL;
		ft_delete_list(&tmp->argv);
		ft_lstdel_re(&tmp->re);
		free((void *) tmp);
		tmp = NULL;
	}
}

t_command	*ft_last_cmd(t_command *cmd)
{
	t_command	*tmp;

	tmp = cmd;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
