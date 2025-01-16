/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:16:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 12:58:18 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*subs;
	size_t	s_len;
	size_t	subs_len;

	if (s == NULL)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (gc_strdup(""));
	if (s_len - start >= len)
		subs_len = len;
	else
		subs_len = s_len - start;
	subs = (char *)gc_malloc (subs_len + 1);
	if (subs == NULL)
		return (NULL);
	ft_strlcpy(subs, s + start, subs_len + 1);
	return (subs);
}
