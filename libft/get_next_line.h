/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:05:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/30 16:03:36 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include "libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 2000
# endif

size_t	len(char *str);
size_t	newline(char *str);
int		ft_int_strchr(const char *s, int c);

char	*get_next_line(int fd);
char	*line_from_leftover(char *leftover, size_t line_len, size_t add);
char	*new_left(char *lftvr, size_t line_len, size_t lftvr_len, char *line);
char	*add_chunk(char *leftover, char *buffer, size_t bytes_read);
char	*free_leftover(char *leftover);
#endif