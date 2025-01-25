/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:55:00 by ewu               #+#    #+#             */
/*   Updated: 2025/01/25 13:24:32 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	input(t_redir *redir, int fd, int *exit_status)
static int	input(t_redir *redir, int fd)
{
	if (fd != 0)
		close(fd);
	fd = open(redir->left, O_RDONLY, 00644); //In this specific code snippet, the permission mode argument is redundant since O_RDONLY is just opening an existing file for reading - the mode argument is only used when creating new files (with O_CREAT flag).
	if (fd != -1)
	{
		// *exit_status = 0;
		return (fd);
	}
	print_err(redir->left, NULL, strerror(errno));
	// *exit_status = 1;
	return (-1);
}

int	exec_in(t_redir *redir, t_data *data)
{
	int	fd;

	fd = 0;
	if (redir)
	{
		// fd = input(redir, fd, &data->exit_status);
		fd = input(redir, fd);
		if (fd < 0)
			return (data->exit_status = 1, -1);
	}
	data->fd[0] = fd;
	data->exit_status = 0;
	return (0);
}


// static int	heredoc(t_redir *redir, int fd, int *exit_status)
// {
// 	if (fd != 0)
// 		close(fd);
// 	fd = redir->heredoc_fd;
// 	if (fd != -1)
// 	{
// 		*exit_status = 0;
// 		return (fd);
// 	}
// 	print_err("heredoc", redir->left, strerror(errno));
// 	*exit_status = 1;
// 	return (-1);
// }