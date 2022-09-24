/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * return number len
 */
size_t	ft_get_int_len(long n, int sign)
{
	size_t	i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	if (sign == -1)
		i++;
	return (i);
}

/*
 * integer to alpha
 */
char	*ft_int_to_string(long n)
{
	char	*output;
	long	tmp;
	size_t	i;
	int		sign;

	sign = 1;
	if (n < 0)
		sign = -1;
	tmp = (long) n * sign;
	i = ft_get_int_len(tmp, sign);
	output = (char *) malloc(i + 1);
	if (!output)
		return (NULL);
	output[i--] = '\0';
	while (tmp > 9)
	{
		output[i] = (char)(tmp % 10) + '0';
		tmp = tmp / 10;
		i--;
	}
	output[i] = (char)(tmp % 10) + '0';
	if (sign == -1)
		output[0] = '-';
	return (output);
}

/*
 * write string in file descriptor
 */
void	ft_write_fd(int fd, char *s)
{
	write(fd, s, ft_strlen(s));
}

/*
 * write string and new line in file descriptor
 */
void	ft_write_fd_nl(int fd, char *s)
{
	ft_write_fd(fd, s);
	write(fd, "\n", 1);
}

/*
 * find and return char in the string or return NULL
 */
char	*ft_char_in_str(const char *s, const char c)
{
	char	*tmp;

	if (!s || !c)
		return (NULL);
	tmp = (char *) s;
	while (*tmp)
	{
		if (*tmp == c)
			return ((char *)tmp);
		tmp++;
	}
	return (NULL);
}
