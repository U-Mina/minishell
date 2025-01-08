/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hepler_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:40:19 by ewu               #+#    #+#             */
/*   Updated: 2024/12/27 04:24:26 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * hlper ft from libft
 * and some other costomized helper fts
 * tmp used as notes
 */

//review: some helpler ft from libft
char	*ft_strchr(char *s, char c);
int	ft_strncmp(char *s1, char *s2);// CHECK return 0 if ==
char	*ft_strdup(char *s); // check: add a clean ft inside, NO-NEED
size_t	ft_strlen(char *s);
char	*ft_strjoin(char *dst, char *src);
int	ft_isdigit(int i);//check: rerurn 1 if all digit


//args function
size_t args_nbr(char **arr)
{
	size_t i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

// wrapper ft
char	*safe_join(char *s1, char *s2)
{
	size_t	l1;
	size_t	l2;
	char	*res;

	// if (!s1 || !s2)
	// 	return (NULL);
	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	res = safe_malloc(sizeof(char) * (l1 + l2 + 1));
	ft_memcpy((char *)res, s1, l1);
	ft_memcpy((char *)(res + l1), s2, l2);
	res[l1 + l2] = '\0';
	if (res == NULL)
		return (NULL); //check: no need NULL check when call safejoin anymore?
	return (res);
}

void	*safe_malloc(size_t size)
{
	void	*retval;

	retval = malloc(size);
	if (!retval)
	{
		perror("malloc: ");
		exit(EXIT_FAILURE);
	}
	return (retval);
}

void	*ft_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;
	size_t	cpy;

	if (new == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (safe_malloc(new));
	new_ptr = safe_malloc(new);
	cpy = (old < new) ? old : new;
	ft_memcpy(new_ptr, ptr, cpy);
	free(ptr);
	return (new_ptr);
}

void	*gab_collect(void);