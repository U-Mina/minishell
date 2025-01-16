/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 14:55:04 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 15:50:38 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	f_word_count(char const *s, char c)
{
	size_t	word;
	size_t	word_count;

	word = 0;
	word_count = 0;
	while (s[word] != '\0')
	{
		if (s[word] != c && (word == 0 || s[word - 1] == c))
			word_count++;
		word++;
	}
	return (word_count);
}

static char	**free_split(char **arr, size_t i)
{
	while (i > 0)
	{
		free(arr[i]);
		i--;
	}
	gc_free(arr[0]);
	gc_free(arr);
	return (NULL);
}

static size_t	get_start(char const *s, size_t i_start, char c)
{
	while (s[i_start] == c && s[i_start] != '\0')
		i_start++;
	return (i_start);
}

static size_t	get_len(char const *s, size_t i_start, char c)
{
	size_t	word_len;

	word_len = 0;
	while (s[i_start + word_len] != c && s[i_start + word_len] != '\0')
		word_len++;
	return (word_len);
}

char	**gc_split(char const *s, char c)
{
	char	**arr;
	size_t	word;
	size_t	word_count;
	size_t	i;

	if (!s)
		return (NULL);
	word_count = f_word_count(s, c);
	arr = (char **)gc_malloc((word_count + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	word = 0;
	i = 0;
	while (word < word_count)
	{
		i = get_start(s, i, c);
		arr[word] = ft_substr(s, i, get_len(s, i, c));
		if (arr[word] == NULL)
			return (free_split(arr, word));
		word++;
		i = i + get_len(s, i, c);
	}
	arr[word] = NULL;
	return (arr);
}
