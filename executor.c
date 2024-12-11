/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/11 12:58:50 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//think properly how to proceed. This is just a copy of the logic of AST printing, that should be adapted to executing
void	exec_ast(t_astnode *root)
{
	if (ast_node->token->type == PIPE || ast_node->token->type == REDIRECTION)
	{
		//create the pipe, fork and make the child execute one of the parts (left / right, etc)
		exec_ast(ast_node->left);
		exec_ast(ast_node->right);
	}
	if (ast_node->token->type == COMMAND_BINARY || ast_node->token->type == COMMAND_BUILTIN)
	{
		
		while (ast_node->next_arg)
		{
			//take argument somehow
			ast_node = ast_node->next_arg;
		}
	}
}
