/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 10:39:59 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 12:04:59 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//allocates in heap using malloc, returns a pointer to the allocated memory and adds this pointer to a gc_list (garbage collector list) to keep track and clean all allocated items when needed
void	*gc_malloc(size_t size)
{
	void	*allocated;

	allocated = malloc(size);
	if (!allocated)
	{
		gc_malloc_error();
		return (NULL);
	}
	add_gc_list(allocated);
	return (allocated);
}

//frees one allocated element from the gc_list and from heap
void	gc_free(void *free_ptr)
{
	t_gc_list	**gc_list;
	t_gc_list	*current;
	t_gc_list	*prev;

	gc_list = get_gc_list();
	current = *gc_list;
	prev = NULL;
	while (current != NULL)
	{
		if (current->allocated == free_ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				(*gc_list) = current->next;
			free(current->allocated);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

//frees all the string elements in a double pointer, and the double pointer itself
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		gc_free(str[i]);
		i++;
	}
	gc_free(str);
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
	*gc_list = NULL;
}

//reallocates enough space for a size of "new" into a ptr that had "old" size space
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
