/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:19:37 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 13:10:17 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	needle_len;

	i = 0;
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (i + j < len && needle[j] == haystack[i + j] && needle[j])
			j++;
		if (j == needle_len)
			return ((char *)haystack + i);
		else
			i++;
	}
	return (NULL);
}
