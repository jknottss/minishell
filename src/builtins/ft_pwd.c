/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 22:43:52 by jknotts          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * print path where we are
 */
int	ft_pwd(t_data *data, t_command *cmd)
{
	ft_write_fd_nl(cmd->fd->out, &data->pwd[ft_pos_in_string \
	(data->pwd, '=') + 1]);
	return (RETURN_SUCCESS);
}
