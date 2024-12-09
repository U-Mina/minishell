/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:54:09 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:47 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include <stdio.h>*/
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int	i;
	unsigned int	s_len;

	i = 0;
	if (s == NULL)
		return ;
	s_len = (unsigned int)ft_strlen(s);
	while (i < s_len)
	{
		f(i, &s[i]);
		i++;
	}
}

/*int	main(void)
{
	char	s[]="Hello World!";

	printf("before: %s\n", s);
	ft_striteri(s, ft_toupper);
	printf("after: %s", s);
	return (0);
}*/
