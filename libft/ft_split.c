/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:34:53 by ewu               #+#    #+#             */
/*   Updated: 2024/10/14 08:30:13 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_substr(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
			if (s[i] == '\0')
				return (count);
		}
		i++;
	}
	return (count);
}

static char	*make_substr(char const *s, char c)
{
	char	*substr;
	size_t	sublen;
	int		i;

	i = 0;
	sublen = 0;
	while (s[sublen] != '\0' && s[sublen] != c)
		sublen++;
	substr = (char *)malloc(sizeof(char) * (sublen + 1));
	if (substr == NULL)
		return (NULL);
	while (s[i] != '\0' && s[i] != c)
	{
		substr[i] = s[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

static char	**ft_free(char **substr_arr)
{
	size_t	i;

	i = 0;
	while (substr_arr[i])
	{
		free(substr_arr[i]);
		i++;
	}
	free(substr_arr);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**substr_arr;
	int		substr_pos;

	substr_pos = 0;
	substr_arr = (char **)malloc(sizeof(char *) * (count_substr(s, c) + 1));
	if (s == NULL || substr_arr == NULL)
		return (NULL);
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			substr_arr[substr_pos] = make_substr(s, c);
			if (substr_arr[substr_pos] == NULL)
				return (ft_free(substr_arr));
			else
				substr_pos++;
			while (*s != '\0' && *s != c)
				s++;
		}
	}
	substr_arr[substr_pos] = NULL;
	return (substr_arr);
}

// l74: substr_arr[substr_pos] = make_substr(s, c) or
// *substr_arr[substr_pos] = make_substr(s, c)
// return a ptr to an array of str(substr after split)
// count substr - allocate memory - split str - null terminator
// line26: new substr found, not delimiter
// line 30: reach the end -> given the last char is the delimiter
// l32: at this position, it is the delimer (s[i] == c), so move forward