/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:15:50 by ewu               #+#    #+#             */
/*   Updated: 2024/10/10 13:53:55 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	tofind;

	tofind = (char)c;
	while (*s)
	{
		if (*s == tofind)
			return ((char *)s);
		s++;
	}
	if (tofind == '\0')
		return ((char *)s);
	return (NULL);
}
//(char *)s is the pointer to a char
//*s dereference s, the value of the first char in str
//s is the memory address of the first char in str