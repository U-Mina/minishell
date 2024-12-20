/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:55:36 by ewu               #+#    #+#             */
/*   Updated: 2024/10/12 14:40:38 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	new = (char *)malloc(sizeof(char) * (end - start + 1));
	if (new == NULL)
		return (NULL);
	ft_strlcpy(new, &s1[start], end - start + 1);
	return (new);
}

// the lenth of new str is 'end - start', with '\0' at end
//+1 for memory allocation
//l28: if (start > end)
//		return (ft_strdup(s1 + end)) in this case, all chars are trimmed, so 
//return empty str, (s1 + end) point to the NULL terminor of s1 (end = len)