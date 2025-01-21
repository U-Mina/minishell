/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:39:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/21 16:01:12 by ipuig-pa         ###   ########.fr       */
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
//if malloc fails, exit whole program
void	gc_malloc_error(void)
{
	t_gc_list	**gc_list;

	gc_list = get_gc_list();
	if (gc_list)
	{
		gc_clean();
		perror ("Heap allocation fail\n");
		exit(EXIT_FAILURE);
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

void	*gc_realloc(void *ptr, size_t old, size_t new)
{
	void	*new_ptr;
	size_t	cpy;

	if (new == 0)
	{
		gc_free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (gc_malloc(new));
	new_ptr = gc_malloc(new);
	cpy = new;
	if (old < new)
		cpy = old;
	ft_memcpy(new_ptr, ptr, cpy);
	gc_free(ptr);
	return (new_ptr);
}
