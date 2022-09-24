/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  jknotts <jknotts@student.21-school>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 22:43:52 by jknotts           #+#    #+#             */
/*   Updated: 2022/09/24 23:07:18 by                  ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../minishell.h"

/*
 * find and return last position char in the string
 */
int	ft_last_pos_in_string(char *s, char c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return (i);
		i--;
	}
	return (i);
}

/*
 * function for split - count words in string
 */
size_t	ft_words_in_str(char const *s, const char c)
{
	size_t	word_count;

	word_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			while (*s && *s != c)
				s++;
			word_count++;
		}
	}
	return (word_count);
}

/*
 * func for split - create substring
 */
static void	ft_create_substrings(char const *s, const char c, char **array)
{
	size_t	i;
	size_t	word_count;

	i = 0;
	word_count = 0;
	while (*s)
	{
		if (*s == c)
			s++;
		else
		{
			i = 0;
			while (s[i] && s[i] != c)
				i++;
			array[word_count] = ft_get_substring(s, 0, i);
			word_count++;
			s += i;
		}
	}
	array[word_count] = NULL;
}

/*
 * split :)
 */
char	**ft_split(char const *s, const char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **) malloc((ft_words_in_str(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_substrings(s, c, array);
	return (array);
}

/*
 * numb of occurrences of a character in a string
 */
size_t	ft_count_of_in_str(const char *s, const char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		if (*s == c)
			count++;
		s++;
	}
	return (count);
}
