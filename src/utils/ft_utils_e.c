#include "../../minishell.h"

/*
 * delete character from the string
 */
char	*ft_remove_char(char *s, char c)
{
	char	*output;
	char	*tmp;
	int		i;
	int		count;

	count = ft_count_of_in_str(s, c);
	if (count == 0)
		return (s);
	tmp = s;
	output = (char *) malloc((ft_strlen(s) - count) + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			output[i] = *s;
			i++;
		}
		s++;
	}
	output[i] = '\0';
	free((void *) tmp);
	return (output);
}

/*
 * free memory
 */
void	ft_free_char_array(char **array)
{
	size_t	i;

	i = 0;
	while (array && array[i])
	{
		free((void *) array[i]);
		array[i] = NULL;
		i++;
	}
	free((void *) array);
	array = NULL;
}

/*
 * return pos in the string
 */
int	ft_pos_in_string(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

/*
 * use in the sort list - swap nodes
 */
void	ft_swap(t_envp **first, t_envp *swap_a)
{
	t_envp	*tmp;
	t_envp	*swap_b;

	if (!first || !swap_a)
		return ;
	tmp = *first;
	while (tmp && tmp != swap_a && tmp->next != swap_a)
		tmp = tmp->next;
	swap_b = swap_a->next;
	swap_a->next = swap_b->next;
	swap_b->next = swap_a;
	if (*first == swap_a)
	{
		*first = swap_b;
	}
	else
		tmp->next = swap_b;
}

/*
 * sort envp list
 */
void	ft_sort_list(t_envp **envp)
{
	t_envp	*tmp;
	int		sorted;
	int		equation;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		tmp = *envp;
		while (tmp && tmp->next)
		{
			equation = ft_strncmp(tmp->var, tmp->next->var, \
			ft_pos_in_string(tmp->var, '='));
			if (equation > 0)
			{
				ft_swap(envp, tmp);
				sorted = 0;
			}
			else
				tmp = tmp->next;
		}
	}
}
