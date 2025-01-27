/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_out.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:58:40 by ewu               #+#    #+#             */
/*   Updated: 2025/01/27 10:35:39 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	out_or_append(t_redir *redir, int fd)
{
 if (fd != 1)
	 	close(fd);
	if (redir->type == OUTPUT)
		fd = open(redir->left, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
	else if (redir->type == APPEND)
		fd = open(redir->left, (O_CREAT | O_WRONLY | O_APPEND), 00644);
	if (fd == -1)
	{
		print_err(redir->left, NULL, strerror(errno));
		//*exit_status = 1;
		return (-1);
	}
	// *exit_status = 0;
	return (fd);
}

int	exec_out(t_redir *redir, t_data *data)
{
	int	fd;

	fd = 1;
	if (redir)
	{
		fd = out_or_append(redir, fd);
		if (fd < 0)
		{
			data->fd[1] = 1;
			return (data->exit_status = 1, -1);
		}
	}
	data->fd[1] = fd;
	data->exit_status = 0;
	return (0);
}
// static int	out_or_append(t_redir *redir, int fd, int *exit_status)

//debug below

// static int	output(t_redir *redir, int fd, int *exit_status)
// {
// 	if (fd != 1)
// 		close(fd);
// 	fd = open(redir->left, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
// 	if (fd == -1)
// 	{
// 		print_err(redir->left, NULL, strerror(errno));
// 		*exit_status = 1;
// 		return (-1);
// 	}
// 	*exit_status = 0;
// 	return (fd);
// }

// static int	append(t_redir *redir, int fd, int *exit_status)
// {
// 	if (fd != 1)
// 		close(fd);
// 	fd = open(redir->left, (O_CREAT | O_WRONLY | O_APPEND), 00644);
// 	if (fd == -1)
// 	{
// 		print_err(redir->left, NULL, strerror(errno));
// 		*exit_status = 1;
// 		return (-1);
// 	}
// 	*exit_status = 0;
// 	return (fd);
// }
// static int	out_or_append(t_redir *redir)
// {
// 	int fd;
	
// 	fd = -1;
// 	if (redir->type == OUTPUT)
// 		fd = open(redir->left, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
// 	else if (redir->type == APPEND)
// 		fd = open(redir->left, (O_CREAT | O_WRONLY | O_APPEND), 00644);
// 	else
// 		return -1;
		
// 	if (fd == -1)
// 	{
// 		print_err(redir->left, NULL, strerror(errno));
// 		//*exit_status = 1;
// 		return (-1);
// 	}
// 	// *exit_status = 0;
// 	return (fd);
// }

// int	exec_out(t_redir *redir, t_data *data)
// {
// 	int	fd;

// 	fd = -1;
// 	if (redir)
// 	{
// 		fd = out_or_append(redir);
// 		if (fd < 0)
// 		{
// 			data->fd[1] = 1;
// 			return (data->exit_status = 1, -1);
// 		}
// 	}
// 	if (data->fd[1] != 1)
// 		close(data->fd[1]);
// 	data->fd[1] = fd;
// 	data->exit_status = 0;
// 	return (0);
// }
// //debug above