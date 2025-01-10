/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 10:53:18 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 11:47:36 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*handle_error(t_gc_list *gc_list)
{
	gc_clean(gc_list);
	//or exit or something like this
	perror ("Heap allocation fail\n");
	return (NULL);
}
