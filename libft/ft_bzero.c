/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:47:55 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/13 12:31:28 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>
#include <string.h>*/
#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/*
int	main(void)
{
	char	b1[15] = "Hello world";
	char	b2[15] = "Hello world";
	size_t	len = 4;

	ft_bzero(b1, len);
	bzero(b2, len);
	printf("you: %c, %c, %c, %c, %c, bzero: %c, %c, %c, %c, %c", 
	b1[0], b1[1], b1[2], b1[3], b1[4], b2[0], b2[1], b2[2], b2[3], b2[4]);
	return (0);
}
*/
