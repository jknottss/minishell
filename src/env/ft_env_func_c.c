#include "../../minishell.h"

/*
 * func for get path, use for envp and wildcards
 */
void	ft_get_filter_path(char *input, char **path, char **filter)
{
	int		slash;

	slash = ft_last_pos_in_string(input, '/');
	if (slash >= 0)
	{
		*path = ft_get_substring(input, 0, slash + 1);
		*filter = ft_string_dup(&input[slash + 1]);
	}
	else
	{
		*path = ft_string_dup(".");
		*filter = ft_string_dup(input);
	}
}

/*
 * open and read directory
 */
t_envp	*ft_get_files(char *path)
{
	struct dirent	*content;
	DIR				*dir;
	t_envp			*list;

	list = NULL;
	dir = opendir(path);
	if (!dir)
		return (NULL);
	content = readdir(dir);
	while (content)
	{
		if (content->d_name[0] != '.')
			ft_lstadd_back(&list, ft_lstnew(content->d_name));
		content = readdir(dir);
	}
	closedir(dir);
	free((void *) path);
	return (list);
}

/*
 * count nodes envp in list
 */
int	ft_count_of_envp(t_envp *envp)
{
	t_envp	*tmp;
	int		i;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}
