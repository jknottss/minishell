#include "../minishell.h"

/*
 * check string valid
 */
int	ft_check_validity(char *argv)
{
	int	i;

	i = 0;
	if ((argv[0] >= '0' && argv[0] <= '9') || argv[0] == '=')
		return (0);
	while (argv[i] && argv[i] != '=')
	{
		if ((argv[i] < 'A' || argv[i] > 'Z')
			&& (argv[i] < 'a' || argv[i] > 'z')
			&& (argv[i] < '0' || argv[i] > '9')
			&& argv[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
