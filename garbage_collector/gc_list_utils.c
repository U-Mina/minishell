/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_list_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:39:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 15:50:43 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns a pointer to the first element of gc_list (garbage collector list)
t_gc_list	**get_gc_list(void)
{
	static t_gc_list	*gc_list = NULL;

	if (gc_list == NULL)
	{
		gc_list = (t_gc_list *)malloc(sizeof(t_gc_list));
		if (!gc_list)
			return (NULL);
		gc_list->allocated = NULL;
		gc_list->next = NULL;
	}
	return (&gc_list);
}

//add a new node to the gc_list with a pointer to the new_allocated item
void	add_gc_list(void *new_alloc)
{
	t_gc_list	*new_node;
	t_gc_list	*current;

	current = *get_gc_list();
	if (current->allocated == NULL)
		current->allocated = new_alloc;
	else
	{
		while (current->next != NULL)
			current = current->next;
		new_node = (t_gc_list *)malloc(sizeof(t_gc_list));
		if (!new_node)
			gc_malloc_error();
		current->next = new_node;
		new_node->allocated = new_alloc;
		new_node->next = NULL;
	}
}
