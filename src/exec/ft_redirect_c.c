/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:35:21 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

t_return	ft_redirect_in(t_command *cmd, t_re *re)
{
	if (!re->next)
	{
		if (cmd->fd->in > 2)
			close(cmd->fd->in);
		cmd->fd->in = open(re->file, O_RDONLY);
		if (cmd->fd->in < 0)
		{
			ft_print_error(cmd, ERR_FD, re->file);
			return (RETURN_ERROR);
		}
	}
	else if (access(re->file, R_OK) == RETURN_ERROR)
	{
		ft_print_error(cmd, ERR_FD, re->file);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

t_return	ft_redirect_out(t_command *cmd, t_re *re)
{
	if (cmd->fd->out > 2)
		close(cmd->fd->out);
	cmd->fd->out = open(re->file, O_CREAT | O_WRONLY | O_TRUNC, FILE_RIGHTS);
	if (cmd->fd->out < 0)
	{
		ft_print_error(cmd, errno, NULL);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

t_return	ft_redirect_out_out(t_command *cmd, t_re *re)
{
	if (cmd->fd->out > 2)
		close(cmd->fd->out);
	cmd->fd->out = open(re->file, O_CREAT | O_WRONLY | O_APPEND, FILE_RIGHTS);
	if (cmd->fd->out < 0)
	{
		ft_print_error(cmd, errno, NULL);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}
