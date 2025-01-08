/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:58:40 by ewu               #+#    #+#             */
/*   Updated: 2025/01/06 22:46:39 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int out_or_appen(t_redir *redir, int fd, int *exit_status)
{
	if (redir->token->type == OUTPUT)
		return (output(redir, fd, exit_status));
	else if (redir->token->type == APPEND)
		return (append(redir, fd, exit_status));
	return -1;
}

static int output(t_redir *redir, int fd, int *exit_status)
{
	if (fd != 1)
		close(fd);
	fd = open(redir->token->value, (O_CREAT | O_WRONLY | O_TRUNC), 00644);
	if (fd != -1)
	{
		*exit_status = 0;	
		reurn (fd);
	}
	print_err(redir->token->value, NULL, strerror(errno));
	*exit_status = 1;
	return -1;
}

static int append(t_redir *redir, int fd, int *exit_status)
{
	if (fd != 1)
		close(fd);
	fd = open(redir->token->value, (O_CREAT | O_WRONLY | O_APPEND), 00644);
	if (fd != -1)
	{
		*exit_status = 0;	
		reurn (fd);
	}
	print_err(redir->token->value, NULL, strerror(errno));
	*exit_status = 1;
	return -1;
}

int ft_out(t_astnode *astnode, int *exit_status)
{
	int fd;
	t_redir *redir;
	
	fd = 1;
	while (redir)
	{
		fd = out_or_appen(redir, fd, exit_status);
		if (fd < 0)
			return -1;
		redir = redir->right;
	}
	astnode->fd[1] = fd;
	return 0;
}