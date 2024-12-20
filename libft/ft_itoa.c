/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:44:22 by ewu               #+#    #+#             */
/*   Updated: 2024/10/11 16:59:42 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		len = 1;
	if (n < 0)
		len += 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t			len;
	unsigned int	num;
	char			*nstr;

	len = ft_intlen(n);
	nstr = (char *)malloc(sizeof(char) * (len + 1));
	if (nstr == NULL)
		return (NULL);
	if (n < 0)
	{
		nstr[0] = '-';
		num = -n;
	}
	else
		num = n;
	if (num == 0)
		nstr[0] = '0';
	nstr[len] = '\0';
	while (num != 0)
	{
		nstr[len - 1] = (num % 10) + '0';
		num = num / 10;
		len--;
	}
	return (nstr);
}
