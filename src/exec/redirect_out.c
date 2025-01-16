/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:58:40 by ewu               #+#    #+#             */
/*   Updated: 2025/01/15 13:40:30 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int out_or_appen(t_redir *redir, int fd, int *exit_status)
{
	if (redir->type == OUTPUT)
		return (output(redir, fd, exit_status));
	else if (redir->type == APPEND)
		return (append(redir, fd, exit_status));
	return -1;
}

static int output(t_redir *redir, int fd, int *exit_status)
{
	if (fd != 1)
		close(fd);
	fd = open(redir->left, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
	if (fd == -1)
	{
		print_err(redir->left, NULL, strerror(errno));
		*exit_status = 1;
		return -1;
	}
	*exit_status = 0;	
	return (fd);
}

static int append(t_redir *redir, int fd, int *exit_status)
{
	if (fd != 1)
		close(fd);
	fd = open(redir->left, (O_CREAT | O_WRONLY | O_APPEND), 00644);
	if (fd == -1)
	{
		print_err(redir->left, NULL, strerror(errno));
		*exit_status = 1;
		return -1;
	}
	*exit_status = 0;	
	return (fd);
}

int ft_out(t_data *data)
{
	int fd;
	t_redir *redir;
	
	fd = 1;
	redir = data->ast_root->node_type.redir;
	while (redir)
	{
		fd = out_or_appen(redir, fd, data->exit_status);
		if (fd < 0)
			return -1;
		redir = redir->right->node_type.redir;
	}
	data->ast_root->fd[1] = fd;//pass the fd to node
	return 0;
}
