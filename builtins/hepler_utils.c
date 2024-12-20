/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hepler_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:40:19 by ewu               #+#    #+#             */
/*   Updated: 2024/12/18 18:44:51 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * hlper ft from libft
 * and some other costomized helper fts
 * tmp used as notes
 */

char *ft_strchr(char *s, char c){}
int ft_strncmp(char *s1, char *s2){}
char *ft_strdup(char *s){} //todo: add a clean ft inside, NO-NEED
size_t ft_strlen(char *s){}

void *safe_malloc(size_t size)
{
	void	*retval;
	
	retval = malloc(size);
	if (!retval)
		perror("malloc: ");
	return (retval);
}

