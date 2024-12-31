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

//initiates garbage collector list
t_gc_list	*gc_list_init(t_gc_list *gc_list)
{
	gc_list = (t_gc_list *)malloc(sizeof(t_gc_list));
	if (!gc_list)
		return (NULL);
	gc_list->allocated = NULL;
	gc_list->next = NULL;
	return (gc_list);
}

//design properly having in mind where the linked list is allocated and if it should be on the main and stack or in heap and increase size when new node is added,....
void	*gc_malloc(size_t size, t_gc_list *gc_list)
{
	void	*allocated;

	allocated = malloc(size);
	if (!allocated)
		return (NULL);
	add_gc_list(allocated, gc_list);
	return (allocated);
}

//add a new node to the list, and next
void	*add_gc_list(void *new_alloc, t_gc_list *gc_list)
{
	t_gc_list	*new_node;
	t_gc_list	*current;

	if (gc_list->allocated == NULL)
		gc_list->allocated = new_alloc;
	else
	{
		current = gc_list;
		while (current->next != NULL)
			current = current->next;
		new_node = (t_gc_list *)malloc(sizeof(t_gc_list));
		if (!new_node)
			return (NULL);
		current->next = new_node;
		new_node->allocated = new_alloc;
		new_node->next = NULL;
	}
	return (gc_list);
}

//frees one allocated element from the gc_list and from heap
//BE AWARE IF WE FREE THE FIRST ELEMENT HOW TO HANDLE GC_LIST!! (PASS THROUGH DOUBLE POINTER!?!)
void	gc_free(void *free_ptr, t_gc_list *gc_list)
{
	t_gc_list	*current;

	current = gc_list;
	if(current->allocated == free_ptr)
		free(current->allocated);
	else
	{
		while(current->next->allocated != free_ptr)
			current = current->next;
		free(current->next->allocated);
		current->next = current->next->next;
	}
}

//frees all the allocated elements in the gc_list and heap
void	gc_clean(t_gc_list *gc_list)
{
	t_gc_list	*current;
	t_gc_list	*next;

	current = gc_list;
	while (current->next != NULL)
	{
		next =  current->next;
		free(current->allocated);
		free(current);
		current = next;
	}
	free(current->allocated);
	free(current);
}