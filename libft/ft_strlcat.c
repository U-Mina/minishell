/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:16:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:46 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>
*/
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	if (dstsize <= dst_len)
		return (src_len + dstsize);
	while (i < dstsize - dst_len - 1 && src[i] != '\0')
	{
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (dst_len + ft_strlen(src));
}
/*
int	main(void)
{
	//test cases: size_t: 0, 2, 6, 7, 10, 50
	char src[6] = " hello";
	char dst_you[50] = "world";
	char dst_strlcat[50] = "world";
	size_t dstsize = 0;

	printf("you: %zu, %s;", ft_strlcat(dst_you, src, dstsize), dst_you);
	printf("strlcat: %zu, %s", strlcat(dst_strlcat, src, dstsize), dst_strlcat);
	return (0);
}
*/
