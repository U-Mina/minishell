/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hepler_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:40:19 by ewu               #+#    #+#             */
/*   Updated: 2025/01/29 12:59:43 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * hlper ft from libft
 * and some other costomized helper fts
 * tmp used as notes
 */

// //review: some helpler ft from libft
// char	*ft_strchr(char *s, char c);
// int	ft_strncmp(char *s1, char *s2);// CHECK return 0 if ==
// char	*ft_strdup(char *s); // check: add a clean ft inside, NO-NEED
// size_t	ft_strlen(char *s);
// char	*ft_strjoin(char *dst, char *src);
// int	ft_isdigit(int i);//check: rerurn 1 if all digit

//args function
int	args_nbr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void	print_err(char *s1, char *s2, char *s3)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
	{
		ft_putstr_fd(s2, 2);
		ft_putstr_fd(": ", 2);
	}
	if (s3)
	{
		ft_putstr_fd(s3, 2);
		ft_putstr_fd("\n", 2);
	}
}
