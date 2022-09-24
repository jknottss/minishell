/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * execute redirect
 */
void	ft_do_redirections(t_command *cmd, t_re *re)
{
	while (cmd)
	{
		re = cmd->re;
		while (re)
		{
			if (ft_strcmp(re->direct, "<"))
			{
				if (ft_redirect_(cmd, re, ft_redirect_in) == RETURN_ERROR)
					break ;
			}
			else if (ft_strcmp(re->direct, ">"))
			{
				if (ft_redirect_(cmd, re, ft_redirect_out) == RETURN_ERROR)
					break ;
			}
			else if (ft_strcmp(re->direct, ">>"))
			{
				if (ft_redirect_(cmd, re, ft_redirect_out_out) == RETURN_ERROR)
					break ;
			}
			re = re->next;
		}
		cmd = cmd->next;
	}
}

/*
 * check valid redirect and do it
 */
t_return	ft_do_valid_redirections(t_data *data)
{
	t_re		*re_tmp;
	t_command	*cmd_tmp;

	cmd_tmp = data->c_line;
	while (cmd_tmp)
	{
		re_tmp = cmd_tmp->re;
		while (re_tmp)
		{
			if (ft_strcmp(re_tmp->direct, "<<"))
				if (ft_redirect_prepare_in_in(data, cmd_tmp, \
				re_tmp->file) == RETURN_ERROR)
					return (RETURN_ERROR);
			re_tmp = re_tmp->next;
		}
		cmd_tmp = cmd_tmp->next;
	}
	cmd_tmp = data->c_line;
	ft_do_redirections(cmd_tmp, re_tmp);
	return (RETURN_SUCCESS);
}

/*
 * prepare redirect
 */
int	ft_redirect_prepare_in_in(t_data *data, t_command *cmd, char *end_term)
{
	if (ft_check_next_token(cmd, end_term) == RETURN_ERROR)
	{
		return (RETURN_ERROR);
	}
	ft_set_parent_heredoc();
	cmd->result = ft_redirect_in_in(data, cmd, end_term);
	ft_set_parent_interactive();
	if (cmd->result == RETURN_ERROR)
	{
		data->errnum = 1;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

/*
 * exec redirect return code
 */
t_return	ft_redirect_(t_command *cmd, t_re *re, \
t_return (*redirect)(t_command *, t_re *))
{
	if (re->file[0] == '\0' || re->file[0] == '<' || re->file[0] == '>'
		|| re->file[0] == '|' || re->file[0] == '*')
	{
		cmd->result = RETURN_ERROR;
		ft_print_error(cmd, ERR_SYNTAX, re->file);
		return (RETURN_ERROR);
	}
	if (redirect(cmd, re) == RETURN_ERROR)
	{
		cmd->result = RETURN_ERROR;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}

/*
 * exec redirect in redirect
 */
t_return	ft_redirect_in_in(t_data *data, t_command *cmd, char *end_term)
{
	int	fd[2];

	if (pipe(fd) == RETURN_ERROR)
		ft_print_error(cmd, errno, NULL);
	if (cmd->fd->in > 2)
		close(cmd->fd->in);
	cmd->fd->in = fd[0];
	if (ft_heredoc(data, fd[1], end_term) == RETURN_ERROR)
	{
		cmd->errnum = 1;
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}
