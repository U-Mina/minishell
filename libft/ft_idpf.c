/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_idpf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:00:24 by ewu               #+#    #+#             */
/*   Updated: 2024/11/08 13:37:24 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_int_extreme(int n, int *count)
{
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) != 11)
			return (*count += -1);
		else
			return (*count += 11);
	}
	else if (n == 2147483647)
	{
		if (write(1, "2147483647", 10) != 10)
			return (*count += -1);
		else
			return (*count += 10);
	}
	return (*count);
}

int	ft_pfid(int n, int *count)
{
	if (n == -2147483648)
		return (ft_int_extreme(n, count));
	else if (n == 2147483647)
		return (ft_int_extreme(n, count));
	else if (n < 0)
	{
		ft_write('-', count);
		ft_pfid(-n, count);
	}
	else if (n >= 10)
	{
		ft_pfid((n / 10), count);
		ft_pfchar((n % 10) + '0', count);
	}
	else
		ft_pfchar(n + '0', count);
	return (*count);
}
