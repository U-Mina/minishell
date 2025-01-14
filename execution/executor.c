/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 11:29:40 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//think properly how to proceed. This is just a copy of the logic of AST printing, that should be adapted to executing
//travels the whole AST starting from the AST_root and redirects to the corresponding function to execute each of the types of nodes
void	exec_ast(t_astnode *ast_node, int *exit_status)
{
	if (ast_node->token->type == PIPE)
		exec_pip(ast_node, exit_status);
	else if (ast_node->token->type == REDIRECTION) //have into account or distinguish between INPUT, OUTPUT, HEREDOC and APPEND
		exec_redir(ast_node, exit_status);
	else if (ast_node->token->type == COMMAND_BUILTIN)
		exec_builtins(ast_node, exit_status);
		//case_match(get_command_args(ast_node)); //(direct to seperate) **
	else if (ast_node->token->type == COMMAND_BINARY)
	{
		get_path(ast_node, exit_status);
		execve(ast_node->node_type.cmd->path, ast_node->node_type.cmd->argv);//adjust env to wherever it is
	}
}
