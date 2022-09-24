/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_f.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:19:37 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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

int	ft_check_heredoc_end_term(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' \
		|| s[i] > 'Z') && (s[i] < '0' || s[i] > '9'))
			return (RETURN_FALSE);
		i++;
	}
	return (RETURN_TRUE);
}
