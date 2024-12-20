/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:54:37 by ewu               #+#    #+#             */
/*   Updated: 2024/10/12 15:26:08 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	sl;
	size_t	dl;

	i = 0;
	sl = ft_strlen(src);
	dl = ft_strlen(dst);
	if (dstsize <= dl)
		return (dstsize + sl);
	while (src[i] && ((i + dl) < dstsize - 1))
	{
		dst[dl + i] = src[i];
		i++;
	}
	dst[i + dl] = '\0';
	return (sl + dl);
}
