/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:26:07 by ewu               #+#    #+#             */
/*   Updated: 2024/10/10 13:55:35 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*mem_size;

	mem_size = (void *)malloc(count * size);
	if (mem_size == NULL)
		return (NULL);
	ft_memset(mem_size, 0, (count * size));
	return (mem_size);
}
// or return (ft_memset(mem_size, 0, size) directly?
//'size' is the the 'size' of bytes of the data type of 'count' already
//so no need to use 'count * sizeof(size)'
//len = count*size byte of '0' will be written to 'mem_size'