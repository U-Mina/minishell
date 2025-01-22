/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_issep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:00:07 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/22 12:00:07 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//checks if the passed character is a separator
int	ft_issep(char c)
{
	unsigned char	u_c;

	u_c = (unsigned char)c;
	if (u_c != c)
		return (0);
	if (u_c == '|' || u_c == '&' || u_c == ';' || u_c == '(' || u_c == ')'  || u_c == '<'  || u_c == '>')  
		return (1);
	return (0);
}