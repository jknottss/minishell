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
