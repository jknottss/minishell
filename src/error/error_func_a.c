#include "../../minishell.h"

/*
 * print err
 */
int	ft_print_error(t_command *cmd, int errnum, char *token)
{
	ft_write_fd(cmd->fd->err, PROMPT);
	if (errnum == ERR_CMD_NOT)
		ft_err_file_cmd(cmd);
	else if (errnum == ERR_FILE)
		ft_err_file(cmd);
	else if (errnum == ERR_SYNTAX)
		ft_err_syntax(cmd, token);
	else if (errnum == ERR_NOT_VALID)
		ft_err_not_valid(cmd, token);
	else if (errnum == ERR_NUMERIC)
		ft_err_numeric(cmd, token);
	else if (errnum == ERR_TOO_ARG)
		ft_err_too_arg(cmd);
	else if (errnum == ERR_CD_FOLDER)
		ft_err_cd_folder(cmd, token);
	else if (errnum == ERR_FD)
		ft_err_fd(cmd, token);
	else
		ft_err_else(cmd, errnum);
	return (RETURN_ERROR);
}

/*
 * while err in file command
 */
void	ft_err_file_cmd(t_command *cmd)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	if (ft_char_in_str(cmd->cmd, '/'))
		ft_write_fd(cmd->fd->err, ": no such file or directory\n");
	else
		ft_write_fd(cmd->fd->err, ": command not found\n");
	cmd->errnum = 127;
}

/*
 * while err with file
 */
void	ft_err_file(t_command *cmd)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": No such file or directory\n");
	cmd->errnum = 127;
}

/*
 * syntax err
 */
void	ft_err_syntax(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, "syntax error near unexpected token `");
	if (token && token[0] == '\0')
		ft_write_fd(cmd->fd->err, "newline");
	else
		ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, "'\n");
	cmd->errnum = 258;
}

/*
 * valid err
 */
void	ft_err_not_valid(t_command *cmd, char *token)
{
	ft_write_fd(cmd->fd->err, cmd->cmd);
	ft_write_fd(cmd->fd->err, ": `");
	ft_write_fd(cmd->fd->err, token);
	ft_write_fd(cmd->fd->err, "': not a valid identifier\n");
	cmd->errnum = 1;
}
