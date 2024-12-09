/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:16:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:16:41 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;
	size_t	subs_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (s_len - start >= len)
		subs_len = len;
	else
		subs_len = s_len - start;
	subs = (char *)malloc (subs_len + 1);
	if (subs == NULL)
		return (NULL);
	ft_strlcpy(subs, s + start, subs_len + 1);
	return (subs);
}
