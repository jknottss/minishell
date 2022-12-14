/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * add string in the parse (check) struct
 */
void	ft_add_string(t_parse *check, char *input)
{
	char	*tmp;

	tmp = ft_get_substring(input, check->start, check->i - check->start);
	ft_lstadd_back(&check->str, ft_lstnew(tmp));
	free((void *) tmp);
	check->i_string++;
}

/*
 * use in redirect - check dollar
 */
char	*ft_check_dollar_in_heredoc(char *token, t_data *data)
{
	t_parse	check;

	check.str = NULL;
	check.i = 0;
	check.i_string = 0;
	check.start = 0;
	while (token[check.i])
	{
		if (token[check.i] == '$')
			ft_found_dollar(&check, token, data);
		check.i++;
	}
	if (check.i_string == 0)
		return (token);
	if (check.start != check.i)
		ft_lstadd_back(&check.str, ft_lstnew(&token[check.start]));
	free(token);
	return (ft_prepare_output(check.str));
}

/*
 * use in parser then we find "?"
 */
void	ft_questionmark(t_parse *check, t_data *data)
{
	char	*tmp2;

	tmp2 = ft_int_to_string((long) data->errnum);
	ft_lstadd_back(&check->str, ft_lstnew(tmp2));
	free((void *) tmp2);
}

/*
 * use in parser - find "*" in token - wildcard
 */
t_return	ft_check_for_asterisk(t_parser *parser, char *input)
{
	if (ft_char_in_str(input, '*'))
	{
		ft_wildcard(parser->cmd, input);
		return (RETURN_TRUE);
	}
	ft_replace_in_string(input, (unsigned char) 255, '*');
	return (RETURN_FALSE);
}

/*
 * call if we don't have pipes or redirect
 */
void	ft_parser_add_argv(t_data *data, t_parser *parser)
{
	char	*tmp;

	tmp = ft_check_quotes_insert_var(parser, data);
	if (ft_check_for_asterisk(parser, tmp) == RETURN_FALSE)
	{
		if (parser->cmd->cmd)
			ft_lstadd_back(&parser->cmd->argv, ft_lstnew(tmp));
		else
		{
			parser->cmd->cmd = ft_string_dup(tmp);
			parser->cmd->result = RETURN_SUCCESS;
		}
	}
	free((void *) tmp);
}
