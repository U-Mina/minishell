/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 11:58:12 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/09 09:20:46 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <ctype.h>
*/

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}

/*
int	main(void)
{
	int	c;

	c = -1;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	c = 0;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	c = 120;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	c = 127;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	c = 128;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	c = 300;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	c = 2147483647;
	printf("int:%d,", c);
	printf("you:%d,", ft_isascii(c));
	printf("isascii:%d. ", isascii(c));
	return (0);
}
*/
