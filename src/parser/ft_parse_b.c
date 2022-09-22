#include "../../minishell.h"
/*
 * parse token inside double quote
 */
void	ft_inside_d_quote(t_parse *check, char *input, t_data *data)
{
	if (check->i > 0)
		ft_add_string(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '*')
			input[check->i] = (unsigned char) 255;
		if (input[check->i] == '$')
			ft_found_dollar(check, input, data);
		if (input[check->i] == '\"')
		{
			ft_add_string(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

/*
 * parse token inside single quote
 */
void	ft_inside_s_quote(t_parse *check, char *input)
{
	if (check->i > 0)
		ft_add_string(check, input);
	check->start = check->i + 1;
	check->i++;
	while (input[check->i])
	{
		if (input[check->i] == '*')
			input[check->i] = (unsigned char) 255;
		if (input[check->i] == '\'')
		{
			ft_add_string(check, input);
			check->start = check->i + 1;
			break ;
		}
		check->i++;
	}
}

/*
 * if we found dollar in the token
 */
void	ft_found_dollar(t_parse *check, char *input, t_data *data)
{
	char	*tmp;

	if (check->i > 0)
		ft_add_string(check, input);
	tmp = ft_get_var(&input[check->i + 1]);
	if (ft_check_validity(tmp) == 0 && tmp[0] != '?')
		tmp[0] = '\0';
	if (ft_strncmp(tmp, "?", 1) == 0)
		ft_questionmark(check, data);
	else if (ft_strncmp(&input[check->i + 1], "\0", 1) == 0
		|| ft_strncmp(&input[check->i + 1], "\'", 1) == 1
		|| ft_strncmp(&input[check->i + 1], "\"", 1) == 1)
		ft_lstadd_back(&check->str, ft_lstnew("$"));
	else
	{
		ft_lstadd_back(&check->str, ft_lstnew(ft_getenv(tmp, data->envp)));
	}
	check->i_string++;
	check->i += ft_strlen(tmp);
	check->start = check->i + 1;
	free((void *) tmp);
}

/*
 * copy list in output variable (create string from list)
 */
char	*ft_prepare_output(t_envp *list)
{
	char	*output;
	t_envp	*tmp;

	tmp = list;
	output = (char *) malloc(1);
	output[0] = '\0';
	while (tmp)
	{
		output = ft_realloc(output, tmp->var, 1, 0);
		tmp = tmp->next;
	}
	ft_delete_list(&list);
	return (output);
}

/*
 * get next token
 */
char	*ft_get_next_token(t_parser *parser, t_data *data)
{
	char	*output;
	int		len;

	parser->tmp = ft_skip_whitespaces(parser->tmp);
	len = ft_end_of_token(parser->tmp, 0);
	parser->token = ft_get_substring(parser->tmp, 0, len);
	output = ft_check_quotes_insert_var(parser, data);
	free(parser->token);
	parser->token = NULL;
	parser->tmp += len;
	return (output);
}
