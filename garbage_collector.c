/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:39:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/28 10:39:59 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//design properly having in mind where the linked list is allocated and if it should be on the main and stack or in heap and increase size when new node is added,....
void	*gc_malloc(size_t size)
{
	void				*allocated;
	static t_gc_list	*gc_list

	allocated = malloc(size, gc_list);
	gc_list = add_gc_list(allocated);
	return (allocated);
}

//add a new node to the list, and next
void	*add_gc_list(void *new_alloc, t_gc_list *gc_list)
{
	t_gc_list	new_node;

	while ()
	new_node.allocated = allocated;
	new_node.next = NULL;
}

void	gc_free(void *free_ptr, t_gc_list *gc_list)
{
	t_gc_list	*current;

	current = gc_list;
	while(current->next->allocated != free_ptr)
		current = current->next;
	free(current->next->allocated);
	current->next = current->next->next;
}

void	gc_clean(t_gc_list *gc_list)
{
	t_gc_list	*current;

	current = gc_list;
	while (current->next != NULL)
	{
		free(current->allocated);
		current = current->next;
	}
	free(gc_list);
}