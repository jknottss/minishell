/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * some kind of join + free on flags
 */
char	*ft_realloc(char *s1, char *s2, int free_s1, int free_s2)
{
	ssize_t		s1_len;
	char		*output;

	s1_len = ft_strlen(s1);
	output = (char *) malloc(s1_len + ft_strlen(s2) + 1);
	if (!output)
		return (NULL);
	ft_copy(output, s1, 0);
	ft_copy(&output[s1_len], s2, 0);
	if (free_s1)
		free((void *) s1);
	if (free_s2)
		free((void *) s2);
	return (output);
}

/*
 * return len of string
 */
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

/*
 * compare first n characters in strings
 */
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		else if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

/*
 * fill n blocks of memory selected character
 */
void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char		*ptr;
	unsigned char		value;
	size_t				i;

	if (n > 0)
	{
		i = 0;
		ptr = (unsigned char *) s;
		value = (unsigned char) c;
		while (i < n)
		{
			*ptr = value;
			ptr++;
			i++;
		}
	}
	return (s);
}

/*
 * copy string from source to destination
 */
size_t	ft_copy(char *dst, char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (src && size == 0)
	{
		while (src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	else if (src)
	{
		size--;
		while (i < size && src[i])
		{
			dst[i] = src[i];
			i++;
		}
	}
	dst[i] = '\0';
	return (i);
}
