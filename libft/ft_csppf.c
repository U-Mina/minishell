/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csppf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 12:28:18 by ewu               #+#    #+#             */
/*   Updated: 2024/11/08 13:37:51 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * int *count: int type of ptr
 * (*count)++ increment value stored at mem address *count point
 * to, dereferencing the ptr and increment the value
 * but not move the ptr *count to next mem address
 * why doing this:
 * printf fct itself return the number of things printed
 */

void	ft_pfchar(char c, int *count)
{
	ft_write(c, count);
}

/**
 * NULL need to be handled in string specifically, bc str is passed
 * by ptr, while ptr can be NULL, not handled, will segmentation error
 * char and num are passed by value, even null is '\0', always valid
 */
int	ft_pfstr(char *s, int *count)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		if (write (1, "(null)", 6) != 6)
			return (*count += -1);
		else
			return (*count += 6);
	}
	while (s[i])
	{
		ft_write(s[i], count);
		i++;
	}
	return (*count);
}

/**
 * 64-bit requires max 16 char in hex
 * 21 is enough
 * deal with NULL case w.r.t ptr
 */
void	ft_pfptr(size_t ptr, int *count)
{
	int		i;
	char	*hex_small;
	char	holder[21];

	i = 0;
	hex_small = "0123456789abcdef";
	ft_write('0', count);
	ft_write('x', count);
	if (ptr == 0)
	{
		ft_write('0', count);
	}
	while (ptr != 0)
	{
		holder[i] = hex_small[ptr % 16];
		ptr = ptr / 16;
		i++;
	}
	while (i > 0)
	{
		i--;
		ft_pfchar(holder[i], count);
	}
}

// int	result;
// result = write(1, &c, 1);
// if (result == -1)
//(*count) = -1;
// else
//(*count)++;
// return (
