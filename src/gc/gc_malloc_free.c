/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:39:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 15:50:42 by ipuig-pa         ###   ########.fr       */
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
