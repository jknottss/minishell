/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * foo to parse string from readline
 */
void	ft_parser(t_data *data)
{
	t_parser	parser;

	ft_init_parser(&parser, data);
	while (*parser.tmp)
	{
		parser.len = ft_end_of_token(parser.tmp, &parser.inside_echo);
		parser.token = ft_get_substring(parser.tmp, 0, parser.len);
		parser.result = ft_check_cmd(data, &parser);
		if (parser.result == RETURN_ERROR)
			break ;
		if (parser.result == RETURN_TRUE)
			ft_get_re(data, &parser);
		if (parser.result == RETURN_FALSE)
			ft_parser_add_argv(data, &parser);
		ft_free((void *) parser.token);
		if (parser.inside_echo == 0)
			parser.tmp = ft_skip_whitespaces(parser.tmp);
		else
			ft_inside_echo(&parser);
		if (ft_strcmp(parser.cmd->cmd, "echo"))
			parser.inside_echo = 1;
	}
}

/*
 * init parser struct
 */
void	ft_init_parser(t_parser *parser, t_data *data)
{
	data->c_line = ft_create_cmd_elem();
	parser->inside_echo = 0;
	parser->result = 0;
	parser->cmd = data->c_line;
	parser->tmp = data->r_line;
	parser->tmp = ft_skip_whitespaces(parser->tmp);
}

/*
 * return len of token, check inside echo
 */
int	ft_end_of_token(char *s, int *inside_echo)
{
	int	i;

	i = ft_find_end_of_token(s, inside_echo);
	if (i == 0)
	{
		if (ft_strncmp(s, "<<", 2) == 0 || ft_strncmp(s, ">>", 2) == 0
			|| ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0)
			return (2);
		else
			return (1);
	}
	return (i);
}

/*
 * check quote and find len of current token
 */
int	ft_find_end_of_token(char *s, int *inside_echo)
{
	int	i;
	int	s_quote;
	int	d_quote;

	i = 0;
	s_quote = 0;
	d_quote = 0;
	while (s[i])
	{
		ft_check_quote(s[i], &d_quote, &s_quote);
		if (d_quote == 0 && s_quote == 0)
		{
			if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r'))
				break ;
			if (s[i] == '>' || s[i] == '<' || s[i] == '|' || s[i] == '&')
			{
				if (inside_echo)
					*inside_echo = 0;
				break ;
			}
		}
		i++;
	}
	return (i);
}
