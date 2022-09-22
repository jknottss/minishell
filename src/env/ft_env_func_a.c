#include "../../minishell.h"

/*
 * init envp list
 */
t_envp	*ft_lstnew(char *content)
{
	t_envp	*new_element;

	new_element = (t_envp *) malloc(sizeof(t_envp));
	if (!new_element)
		return (NULL);
	new_element->var = ft_string_dup(content);
	new_element->next = NULL;
	return (new_element);
}

/*
 * return last node
 */
t_envp	*ft_lstlast(t_envp *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/*
 * push new node back
 */
void	ft_lstadd_back(t_envp **lst, t_envp *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}

/*
 * deletes list
 */
void	ft_delete_list(t_envp **lst)
{
	t_envp	*tmp;

	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		free((void *) tmp->var);
		free((void *) tmp);
	}
	*lst = NULL;
}

/*
 * get and check symbol in the token
 */
char	*ft_get_var(char *s)
{
	int		i;

	i = 0;
	if (ft_isdigit(s[i]) || (!ft_isalpha(s[i]) && s[i] != '_'))
		return (ft_get_substring(s, 0, 1));
	while (s[i])
	{
		if (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r') || s[i] == '#' \
		|| s[i] == '\"' || s[i] == '\'' || s[i] == '$' || s[i] == '=')
			break ;
		if (s[i] == '?')
		{
			i++;
			break ;
		}
		i++;
	}
	return (ft_get_substring(s, 0, i));
}
