/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:05:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/14 09:38:44 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_c;
	const unsigned char	*src_c;
	size_t				i;

	if (dst == src)
		return (dst);
	dst_c = (unsigned char *)dst;
	src_c = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		i++;
	}
	return (dst);
}
/*
int	main(void)
{
	char	src1[15] = "Hello world";
	char	src2[15] = "Hello world";
	char	dst1[15];
	char	dst2[15];
	size_t	n = 5;

	ft_memcpy(dst1, src1, n);
	memcpy(dst2, src2, n);
	printf("you: %s, memcpy: %s", dst1, dst2);
	return (0);
}
*/
