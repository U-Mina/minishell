/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:04:00 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/11/17 12:47:40 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	size_t		bytes_read;
	static char	*leftover;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (leftover = free_leftover(leftover));
	if (leftover && ft_int_strchr(leftover, '\n'))
	{
		line = line_from_leftover(leftover, newline(leftover), 2);
		leftover = new_left(leftover, newline(leftover), len(leftover), line);
		return (line);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		leftover = add_chunk(leftover, buffer, bytes_read);
		return (get_next_line(fd));
	}
	if (bytes_read == 0 && leftover && *leftover)
		line = line_from_leftover(leftover, len(leftover), 1);
	leftover = free_leftover(leftover);
	return (line);
}

char	*line_from_leftover(char *leftover, size_t line_len, size_t add)
{
	char	*line;

	line = (char *)malloc(line_len + add);
	if (!line)
		return (NULL);
	ft_strlcpy(line, leftover, line_len + add);
	return (line);
}

char	*new_left(char *lftvr, size_t line_len, size_t lftvr_len, char *line)
{
	char	*temp;

	if (!line)
		return (free_leftover(lftvr));
	if (line_len >= lftvr_len - 1)
	{
		free(lftvr);
		return (NULL);
	}
	temp = (char *)malloc(lftvr_len - line_len);
	if (!temp)
	{
		free(lftvr);
		return (NULL);
	}
	ft_strlcpy(temp, (lftvr + line_len + 1), (lftvr_len - line_len));
	free(lftvr);
	return (temp);
}

char	*add_chunk(char *leftover, char *buffer, size_t bytes_read)
{
	char	*temp;
	size_t	leftover_len;

	leftover_len = len(leftover);
	temp = (char *)malloc(bytes_read + leftover_len + 1);
	if (!temp)
	{
		free(leftover);
		return (NULL);
	}
	if (leftover)
	{
		ft_strlcpy(temp, leftover, leftover_len + 1);
		free(leftover);
		ft_strlcat(temp, buffer, bytes_read + leftover_len + 1);
	}
	else
		ft_strlcpy(temp, buffer, bytes_read + 1);
	return (temp);
}

char	*free_leftover(char *leftover)
{
	if (leftover)
	{
		free(leftover);
		leftover = NULL;
	}
	return (leftover);
}

/*#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("prova.txt", 0);
 	line = get_next_line(fd);
	printf("%s", line);
	while ((line = get_next_line(fd)))
	{
		printf("LINE_READ: %s", line);
		free(line);
	}
	 printf("from standard input:");
	while ((line = get_next_line(0)))
	{
		printf("LINE_READ: %s", line);
		free(line);
	} 
	return (0);
}*/