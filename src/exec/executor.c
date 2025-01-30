/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 16:18:08 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data *data)
{
	exec_ast(data->ast_root, data);
	if (data->child_status != 0)
		handle_child_sigquit(data);
}

void	exec_ast(t_astnode *ast_node, t_data *data)
{
	if (data == NULL || ast_node == NULL)
		return ;
	if (ast_node->token->type == PIPE)
		exec_pipe(ast_node->node_type.pipe, data);
	else if (ast_node->token->type == REDIRECTION)
	{
		ast_node = handle_redir_fd(ast_node, data);
		exec_ast(ast_node, data);
	}
	else if (ast_node->token->type == COMMAND)
		exec_cmd(ast_node, data);
}
