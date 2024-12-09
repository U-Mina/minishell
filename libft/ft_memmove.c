/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:10:36 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/13 12:21:55 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_c;
	const unsigned char	*src_c;
	size_t				i;

	dst_c = (unsigned char *)dst;
	src_c = (const unsigned char *)src;
	if (dst < src)
	{
		i = 0;
		while (i < len)
		{
			dst_c[i] = src_c[i];
			i++;
		}
	}
	else if (dst > src)
	{
		i = len;
		while (i > 0)
		{
			dst_c[i - 1] = src_c[i - 1];
			i--;
		}
	}
	return (dst);
}

/*int	main(void)
{
	char	src1[15] = "Hello world";
	char	src2[15] = "Hello world";
	char	dst1[15];
	char	dst2[15];
	size_t	n = 5;

	ft_memmove(dst1, src1, n);
	memmove(dst2, src2, n);
	printf("you: %s, memmove: %s", dst1, dst2);
	return (0);
}
*/
