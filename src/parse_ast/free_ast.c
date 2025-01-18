/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:25:37 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/18 12:57:41 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//in libft or in helpers
//frees all the string elements in a double pointer, and the double pointer itself
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		gc_free(str[i]);
		i++;
	}
	gc_free(str);
}

static void	free_cmd_node(t_astnode *ast_node)
{
	int	arg_flag;

	arg_flag = 0;
	if (ast_node->node_type.cmd->argv)
	{
		arg_flag = 1;
		free_double_pointer(ast_node->node_type.cmd->argv);
	}
	if (ast_node->node_type.cmd->path)
		gc_free(ast_node->node_type.cmd->path);
	gc_free(ast_node->node_type.cmd);
	if (arg_flag == 0)
		gc_free(ast_node->token->value);
	gc_free(ast_node);
}

static void	free_pipe_node(t_astnode *ast_node)
{
	if (ast_node->node_type.pipe->left)
		free_ast(ast_node->node_type.pipe->left);
	if (ast_node->node_type.pipe->right)
		free_ast(ast_node->node_type.pipe->right);
	gc_free(ast_node->node_type.pipe);
	gc_free(ast_node->token->value);
	gc_free(ast_node);
}

static void	free_redir_node(t_astnode *ast_node)
{
	if (ast_node->node_type.redir->left)
		gc_free(ast_node->node_type.redir->left);
	if (ast_node->node_type.redir->right)
		free_ast(ast_node->node_type.redir->right);
	gc_free(ast_node->node_type.redir);
	gc_free(ast_node->token->value);
	gc_free(ast_node);
}

void	free_ast(t_astnode *ast_node)
{
	if (ast_node->token->type == PIPE)
		free_pipe_node(ast_node);
	else if (ast_node->token->type == REDIRECTION)
		free_redir_node(ast_node);
	else if (ast_node->token->type == COMMAND)
		free_cmd_node(ast_node);
}
