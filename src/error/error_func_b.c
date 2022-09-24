/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func_b.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 22:43:52 by jknotts          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * when need number in argument
 */
void	ft_err_numeric(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": ");
	ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, ": numeric argument required\n");
	cmd->errnum = 2;
}

/*
 * to many arg err
 */
void	ft_err_too_arg(t_command *cmd)
{
	ft_write_fd(cmd->fd->err, cmd->argv->var);
	ft_write_fd(cmd->fd->err, ": too many arguments\n");
	cmd->errnum = 2;
}

/*
 * err for builtin cd
 */
void	ft_err_cd_folder(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": ");
	ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, ": No such file or directory\n");
	cmd->errnum = 1;
}

/*
 * fd error
 */
void	ft_err_fd(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, ": No such file or directory\n");
	cmd->errnum = 1;
}

/*
 * for another errors
 */
void	ft_err_else(t_command *cmd, int errnum)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": ");
	ft_write_fd_nl(cmd->fd->err, strerror(errnum));
	cmd->errnum = errnum;
}
