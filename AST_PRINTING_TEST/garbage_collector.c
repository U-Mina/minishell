/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:39:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 15:34:20 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//allocates in heap using malloc, returns a pointer to the allocated memory and adds this pointer to a gc_list (garbage collector list) to keep track and clean all allocated items when needed
void	*gc_malloc(size_t size)
{
	void	*allocated;

	allocated = malloc(size);
	if (!allocated)
		gc_malloc_error();
	add_gc_list(allocated);
	return (allocated);
}

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

//handle allocation failure using gc_malloc, forcing exit and cleaning everything before
void	gc_malloc_error(void)
{
	t_gc_list	**gc_list;

	gc_list = get_gc_list();
	if (gc_list)
	{
		gc_clean();
		perror ("Heap allocation fail\n");
		exit (1);
	}
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

//frees one allocated element from the gc_list and from heap
void	gc_free(void *free_ptr)
{
	t_gc_list	**gc_list;
	t_gc_list	*current;

	gc_list = get_gc_list();
	current = *gc_list;
	if (current->allocated == free_ptr)
	{
		(*gc_list) = current->next;
		free(current->allocated);
	}
	else
	{
		while (current->next->allocated != free_ptr)
			current = current->next;
		free(current->next->allocated);
		current->next = current->next->next;
	}
}

//frees all the allocated elements in the gc_list and heap
void	gc_clean(void)
{
	t_gc_list	**gc_list;
	t_gc_list	*current;
	t_gc_list	*next;

	gc_list = get_gc_list();
	current = *gc_list;
	while (current->next != NULL)
	{
		next = current->next;
		free(current->allocated);
		free(current);
		current = next;
	}
	free(current->allocated);
	free(current);
}
