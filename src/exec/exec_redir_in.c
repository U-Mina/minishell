/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:55:00 by ewu               #+#    #+#             */
/*   Updated: 2025/01/29 13:31:53 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	input(t_redir *redir, int fd)
{
	if (fd != 0)
		close(fd);
	fd = open(redir->left, O_RDONLY, 00644);
	if (fd != -1)
		return (fd);
	print_err(redir->left, NULL, strerror(errno));
	return (-1);
}

int	exec_in(t_redir *redir, t_data *data)
{
	int	fd;

	fd = 0;
	if (redir)
	{
		fd = input(redir, fd);
		if (fd < 0)
		{
			data->exit_status = 1;
			return (-1);
		}
	}
	data->fd[0] = fd;
	data->exit_status = 0;
	return (0);
}
