/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:31:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/10/10 09:31:54 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <ctype.h>
#include <stdio.h>*/

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
int	main(void)
{
	int	c1= 0;
	int	c2= 0;

	printf("you: %d, toupper: %d", ft_toupper(c1), toupper(c2));
	return (0);
}
*/
