/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:34 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/31 17:33:38 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates an init a new node of type CMD for the AST (Abstract Syntax Tree)
t_astnode	*create_cmd_node(t_token *token)
{
	t_astnode	*new_node;

	new_node = (t_astnode *)gc_malloc(sizeof(t_astnode));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	if (new_node->token->type == COMMAND)
	{
		new_node->node_type.cmd = gc_malloc(sizeof(t_cmd));
		if (!new_node->node_type.cmd)
			return (NULL);
		new_node->node_type.cmd->arg_nb = 0;
		new_node->node_type.cmd->argv = NULL;
		new_node->node_type.cmd->path = NULL;
		new_node->node_type.cmd->quote = false;
		if (token->quote == true)
			new_node->node_type.cmd->quote = true;
	}
	else
		return (NULL);
	return (new_node);
}

//creates an init a new node of type REDIR for the AST (Abstract Syntax Tree)
t_astnode	*create_redir_node(t_token *token)
{
	t_astnode	*new_node;

	new_node = (t_astnode *)gc_malloc(sizeof(t_astnode));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	if (new_node->token->type == REDIRECTION)
	{
		new_node->node_type.redir = gc_malloc(sizeof(t_cmd));
		if (!new_node->node_type.redir)
			return (NULL);
		new_node->node_type.redir->left = NULL;
		new_node->node_type.redir->right = NULL;
	}
	else
		return (NULL);
	return (new_node);
}

//creates an init a new node of type PIPE for the AST (Abstract Syntax Tree)
t_astnode	*create_pipe_node(t_token *token)
{
	t_astnode	*new_node;

	new_node = (t_astnode *)gc_malloc(sizeof(t_astnode));
	if (!new_node)
		return (NULL);
	new_node->token = token;
	if (new_node->token->type == PIPE)
	{
		new_node->node_type.pipe = gc_malloc(sizeof(t_cmd));
		if (!new_node->node_type.pipe)
			return (NULL);
		new_node->node_type.pipe->left = NULL;
		new_node->node_type.pipe->right = NULL;
	}
	else
		return (NULL);
	return (new_node);
}
