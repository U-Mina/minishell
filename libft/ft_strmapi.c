/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:22:07 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:44 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*#include <stdio.h>*/

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*s_f;
	unsigned int	i;
	unsigned int	s_len;

	if (s == NULL)
		return (NULL);
	s_len = (unsigned int)ft_strlen(s);
	s_f = (char *)malloc(s_len + 1);
	if (s_f == NULL)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		s_f[i] = f(i, s[i]);
		i++;
	}
	s_f[i] = '\0';
	return (s_f);
}

/*int	main(void)
{
	char	s[]="Hello World!";

	printf("before: %s: after: %s", s, ft_strmapi(s, ft_toupper));
	return (0);
}*/
