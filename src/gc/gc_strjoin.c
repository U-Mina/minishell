/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:30:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/21 11:31:54 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)gc_malloc(s1_len + s2_len + 1);
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str, s2, s1_len + s2_len + 1);
	return (str);
}

char	*safe_join(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = gc_malloc(sizeof(char) * (l1 + l2 + 1));
	ft_memcpy((char *)res, s1, l1);
	ft_memcpy((char *)(res + l1), s2, l2);
	res[l1 + l2] = '\0';
	if (res == NULL)
		return (NULL); 
	return (res);
}
