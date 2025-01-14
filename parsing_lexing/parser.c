/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:49:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 14:01:40 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PENDING:
//Include env variables!! Where??
//Handle parenthesis priorizing redirections
//check if all types of redirections are properly managed
//check if gc_list is properly implemented
//check error handling

//parser (syntactic analysis): builds an Abstract Syntax Tree (AST) using recursive descent parsing, and returns a pointer to AST root. The AST has the tokens as nodes, already correctly classified, and hierarchized.
t_astnode	*parse(t_token *tokens)
{
	t_astnode	*root;
	int			current_token;

	current_token = 0;
	root = parse_command(tokens, &current_token);
	while (tokens[current_token].type != TOKEN_EOF)
	{
		if (tokens[current_token].type == PIPE)
			root = parse_pipe(tokens, &current_token, root);
		if (tokens[current_token].type == REDIRECTION)
			root = parse_redirection(tokens, &current_token, root);
	}
	return (root);
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
	//fd[2] init
	new_node->fd[0] = STDIN_FILENO;
	new_node->fd[1] = STDOUT_FILENO;
	if (new_node->token->type == COMMAND)
	{
		new_node->node_type.cmd = gc_malloc(sizeof(t_cmd));
		// if (!new_node->node_type.cmd)
		// 	return (handle_error(gc_list));
	}
	if (new_node->token->type == PIPE)
	{
		new_node->node_type.pipe = gc_malloc(sizeof(t_pipe));
		// if (!new_node->node_type.pipe)
		// 	return (handle_error(gc_list));
	}
	if (new_node->token->type == REDIRECTION)
	{
		new_node->node_type.redir = gc_malloc(sizeof(t_redir));
		// if (!new_node->node_type.redirect)
		// 	return (handle_error(gc_list));
	}
	return (new_node);
}

//in libft or in helpers
//frees all the string elements in a double pointer, and the double pointer itself
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

// void	free_ast(t_astnode *root);
// {
	
// }