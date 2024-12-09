/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 15:38:29 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/13 12:27:23 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*s_c;
	size_t				i;

	s_c = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_c[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/*int	main(void)
{
	char	s[]="Hello world";
	int		c = 111;
	size_t	n = 15;

	printf("you: %p, memchr: %p", ft_memchr(s, c, n), memchr(s, c, n));
}*/
