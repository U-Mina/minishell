/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uxpf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:28:05 by ewu               #+#    #+#             */
/*   Updated: 2024/11/08 13:37:03 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * the same logic as putnbr in libft
 */

void	ft_pflowx(unsigned int n, int *count)
{
	int		i;
	char	holder[25];
	char	*lowx;

	i = 0;
	lowx = "0123456789abcdef";
	if (n == 0)
	{
		ft_pfchar('0', count);
		return ;
	}
	while (n != 0)
	{
		holder[i] = lowx[n % 16];
		n = n / 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		ft_pfchar(holder[i], count);
	}
}

void	ft_pfhighx(unsigned int n, int *count)
{
	int		i;
	char	holder[25];
	char	*highx;

	i = 0;
	highx = "0123456789ABCDEF";
	if (n == 0)
	{
		ft_pfchar('0', count);
		return ;
	}
	while (n != 0)
	{
		holder[i] = highx[n % 16];
		n = n / 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		ft_pfchar(holder[i], count);
	}
}

/**
 * unsigned int never go down zero, so no need consider <0
 * and then do the same as print int
 */
void	ft_pfu(unsigned int u, int *count)
{
	if (u >= 10)
	{
		ft_pfu((u / 10), count);
		ft_pfchar((u % 10) + '0', count);
	}
	else
		ft_pfchar(u + '0', count);
}
