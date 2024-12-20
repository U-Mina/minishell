/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 15:43:58 by ewu               #+#    #+#             */
/*   Updated: 2024/10/12 11:46:34 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	sl;
	char	*new;

	if (s == NULL)
		return (NULL);
	i = 0;
	sl = ft_strlen(s);
	if (start > sl)
		len = 0;
	if (len > sl - start)
		len = sl - start;
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

// actually chars in 'new' is 'sl-1-start', bc index start at '0'
// add null terminate at the end so the space needed in malloce is 'sl-start'
/*if (start > ft_strlen(s))
	{
		new[0] = '\0';
		return (new);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);*/