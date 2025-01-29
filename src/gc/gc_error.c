/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 12:10:56 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle allocation failure using gc_malloc, forcing exit and cleaning everything before
//if malloc fails, exit whole program
void	gc_malloc_error(void)
{
	t_gc_list	**gc_list;

	gc_list = get_gc_list();
	if (gc_list)
	{
		gc_clean();
		perror ("minishell: heap allocation fail\n");
		// exit(EXIT_FAILURE);
	}
}

void	set_malloc_error(t_data *data)
{
	data->malloc_err = true;
	data->exit_status = 1;
}