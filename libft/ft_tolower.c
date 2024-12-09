/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 13:58:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:40 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>*/

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	return (c);
}

/*
int	main(void)
{
	int	c1= 65;
	int	c2= 65;

	printf("you: %d, tolower: %d", ft_tolower(c1), tolower(c2));
	return (0);
}
*/
