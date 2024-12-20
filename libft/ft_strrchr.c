/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:31:04 by ewu               #+#    #+#             */
/*   Updated: 2024/10/11 16:48:22 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	tofind;
	int		len;

	len = ft_strlen(s);
	tofind = (char)c;
	if (tofind == '\0')
		return ((char *)s + len);
	while (len >= 0)
	{
		if (s[len] == tofind)
			return ((char *)s + len);
		len--;
	}
	return (NULL);
}

// (char *)s casting const char *s to (char *)s, which
// allows pointer arithmetic, and return a mutable pointer (not
// modifying the string itself)
//(char *)s + len indicate the position 'len' char