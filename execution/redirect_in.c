/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 21:55:00 by ewu               #+#    #+#             */
/*   Updated: 2025/01/06 22:47:02 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int in_or_heredoc(t_redir *redir, int fd, int *exit_status)
{
	if (redir->token->type == INPUT)
		return input(redir, fd, exit_status);
	else if (redir->token->type == HEREDOC)
		return heredoc(redir, fd, exit_status);
	return -1;
}

static int input(t_redir *redir, int fd, int *exit_status)
{
	if (fd != 0)
		close(fd);
	fd = open(redir->token->value, O_RDONLY, 00644);
	if (fd != -1)
	{
		*exit_status = 0;	
		reurn (fd);
	}
	print_err(redir->token->value, NULL, strerror(errno));
	*exit_status = 1;
	return -1;
}

static int heredoc(t_redir *redir, int fd, int *exit_status)
{
	if (fd != 0)
		close(fd);
	fd = redir->fd;
	if (fd != -1)
	{
		*exit_status = 0;	
		reurn (fd);
	}
		if (fd != -1)
	{
		*exit_status = 0;	
		reurn (fd);
	}
	print_err(redir->token->value, NULL, strerror(errno));
	*exit_status = 1;
	return -1;
}

int ft_in(t_astnode *astnode, int *exit_status)
{
	int fd;
	t_redir *redir;

	fd = 0;
	redir = astnode->redirect;
	while (redir)
	{
		fd = in_or_heredoc(redir, fd, exit_status);
		if (fd < 0)
			return -1;
		redir = redir->right;
	}
	astnode->fd[0] = fd;
	return 0;
}