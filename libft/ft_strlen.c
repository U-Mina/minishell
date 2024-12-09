/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 09:34:02 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/20 17:32:08 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include <stdio.h>
#include <string.h>
*/
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

/*
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf ("you: %zu, strlen: %zu", ft_strlen(argv[1]), strlen(argv[1]));
	return (0);
}
*/