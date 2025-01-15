/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:02:39 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/15 12:16:42 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strtrim(char const *s1, char const *set)
{
	size_t	s1_len;
	size_t	start;
	size_t	end;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	start = 0;
	while (start < s1_len && ft_strchr(set, (int)s1[start]) != NULL)
		start++;
	end = s1_len;
	while (end > start && ft_strchr(set, (int)s1[end - 1]) != NULL)
		end--;
	return (gc_substr(s1, start, end - start));
}
