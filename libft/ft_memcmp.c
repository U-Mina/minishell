/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:03:32 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/13 12:28:22 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <string.h>
#include <stdio.h>*/
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_c;
	const unsigned char	*s2_c;
	size_t				i;

	s1_c = (const unsigned char *)s1;
	s2_c = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_c[i] == s2_c[i])
			i++;
		else
			return (s1_c[i] - s2_c[i]);
	}
	return (0);
}

/*int	main(void)
{
	char	s1[] = "Hello";
	char	s2[] = "Hell";
	size_t	n = 15;

	printf("you: %d; memcmp: %d", ft_memcmp(s1, s2, n), memcmp(s1, s2, n));
}*/
