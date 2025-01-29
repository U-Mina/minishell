/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 11:12:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 15:39:12 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handle allocation fail using gc_malloc, forcing cleaning everything before
//if malloc fails, exit whole program
void	gc_malloc_error(void)
{
	t_gc_list	**gc_list;

	gc_list = get_gc_list();
	if (gc_list)
	{
		gc_clean();
		perror ("minishell: heap allocation fail\n");
	}
}

//sets the indicator of malloc error to true and the exit status to 1
void	set_malloc_error(t_data *data)
{
	data->malloc_err = true;
	data->exit_status = 1;
}
