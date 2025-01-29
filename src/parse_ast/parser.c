/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:49:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 10:52:19 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PENDING:
//Handle parenthesis priorizing redirections
//check if void commands are correctly implemented
//check error handling

//parser (syntactic analysis): builds an Abstract Syntax Tree (AST) using recursive descent parsing, and returns a pointer to AST root. The AST has the tokens as nodes, already correctly classified, and hierarchized.
int	parse(t_token *tokens, t_data *data)
{
	int	curr_tok;

	curr_tok = 0;
	data->ast_root = NULL;
	while (tokens && tokens[curr_tok].type != TOKEN_EOF)
	{
		if (tokens[curr_tok].type == WORD || \
			tokens[curr_tok].type == REDIRECTION)
			data->ast_root = parse_cmd(tokens, &curr_tok, data);
		if (tokens[curr_tok].type == PIPE)
			data->ast_root = parse_pipe(tokens, &curr_tok, \
														data->ast_root, data);
		if (!data->ast_root)
			break ;
	}
	if (data->ast_root == NULL)
	{
		data->exit_status = 258;
		perror("minishell: syntax error");
		return (0);
	}
	return (1);
}

//creates a new node for the AST (Abstract Syntax Tree)
//
t_astnode	*create_astnode(t_token *token)
{
	t_astnode	*new_node;

	new_node = (t_astnode *)gc_malloc(sizeof(t_astnode));
	// if (!new_node)
	// 	return(handle_error(gc_list));
	new_node->token = token;
	if (new_node->token->type == COMMAND)
	{
		new_node->node_type.cmd = gc_malloc(sizeof(t_cmd));
		// if (!new_node->node_type.cmd)
		// 	return (handle_error(gc_list));
		init_cmd_node(new_node->node_type.cmd);
	}
	if (new_node->token->type == PIPE)
	{
		new_node->node_type.pipe = gc_malloc(sizeof(t_pipe));
		// if (!new_node->node_type.pipe)
		// 	return (handle_error(gc_list));
		init_pipe_node(new_node->node_type.pipe);
	}
	if (new_node->token->type == REDIRECTION)
	{
		new_node->node_type.redir = gc_malloc(sizeof(t_redir));
		// if (!new_node->node_type.redirect)
		// 	return (handle_error(gc_list));
		init_redir_node(new_node->node_type.redir);
	}
	return (new_node);
}
