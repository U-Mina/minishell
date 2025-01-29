/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:28:11 by ewu               #+#    #+#             */
/*   Updated: 2025/01/29 15:28:05 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_fd(t_data *data)
{
	if (data->fd[0] != 0)
	{
		if (dup_err(data->fd[0], STDIN_FILENO) == -1)
			return (data->exit_status = 1, -1);
		close(data->fd[0]);
		data->fd[0] = 0;
	}
	if (data->fd[1] != 1)
	{
		if (dup_err(data->fd[1], STDOUT_FILENO) == -1)
			return (data->exit_status = 1, -1);
		close(data->fd[1]);
		data->fd[1] = 1;
	}
	data->exit_status = 0;
	return (0);
}

static bool	is_quote(t_redir *redir)
{
	if (redir->type == HEREDOC_Q)
		return (true);
	return (false);
}

static int	exec_redir(t_redir *redir, t_data *data)
{
	if (redir->type == HEREDOC || redir->type == HEREDOC_Q)
	{
		exec_heredoc(redir->left, &data->exit_status, data, is_quote(redir));
		if (data->heredoc_fd < 0 || g_signal == SIGINT)
			return (data->exit_status = 1, -1);
	}
	else if (redir->type == INPUT)
	{
		if (exec_in(redir, data) < 0)
			return (-1);
	}
	else if (redir->type == OUTPUT || redir -> type == APPEND)
	{
		if (exec_out(redir, data) < 0)
			return (-1);
	}
	if (update_fd(data) < 0)
	{
		data->exit_status = 1;
		return (-1);
	}
	return (0);
}

t_astnode	*handle_redir_fd(t_astnode *ast_node, t_data *data)
{
	while (ast_node->token->type == REDIRECTION)
	{
		if (exec_redir(ast_node->node_type.redir, data) < 0 || \
			!ast_node->node_type.redir->right)
			return (NULL);
		ast_node = ast_node->node_type.redir->right;
	}
	return (ast_node);
}
