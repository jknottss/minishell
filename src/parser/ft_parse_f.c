#include "../../minishell.h"

/*
 * change len of token if we inside echo
 */
void	ft_inside_echo(t_parser *parser)
{
	parser->len = ft_len_whitespaces(parser->tmp);
	if (parser->len > 0)
		parser->tmp += parser->len;
}

int	ft_check_next_token(t_command *cmd, char *file)
{
	if (file[0] == '\0' || ft_check_heredoc_end_term \
	(file) == RETURN_FALSE)
	{
		ft_print_error(cmd, ERR_SYNTAX, file);
		return (RETURN_ERROR);
	}
	return (RETURN_SUCCESS);
}