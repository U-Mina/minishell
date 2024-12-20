/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 17:24:24 by ewu               #+#    #+#             */
/*   Updated: 2024/10/12 15:10:52 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hs, const char *nd, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (nd[0] == 0)
		return ((char *)hs);
	while (i < len && hs[i])
	{
		while (hs[i + j] == nd[j] && hs[i + j] && ((i + j) < len))
		{
			j++;
			if (nd[j] == 0)
				return ((char *)hs + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
