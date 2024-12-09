/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:19:46 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/05 14:10:43 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdlib.h>
#include <stdio.h>*/

int	ft_atoi(const char *str)
{
	int	integer;
	int	sign;

	integer = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = sign * (-1);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		integer = integer * 10 + (*str - '0');
		str++;
	}
	return (integer * sign);
}

/*int main(void)
{
	char	str[] = "    ++52a4sd";

	printf("you: %d, atoi: %d", ft_atoi(str), atoi(str));
	return (0);
}*/
