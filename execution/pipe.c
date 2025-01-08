/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:03:59 by ewu               #+#    #+#             */
/*   Updated: 2025/01/08 14:14:36 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/minishell.h"

/**
 * - create pipi
 * - redirct and connect pipe
 * - close and clean
//parser (syntactic analysis): builds an Abstract Syntax Tree (AST) using recursive descent parsing, and returns a pointer to AST root. The AST has the tokens as nodes, already correctly classified, and hierarchized.
t_astnode	*parse(t_token *tokens)
//creates AST nodes for commands and their descending nodes arguments
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token)
//adds an argument node as part of the children nodes of a command node
void	add_arg_node(t_astnode *command_node, t_astnode *arg_node)
//parses redirection when present, creating a redirection node, being the left node the command node and the right node the filename
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token)
//parses the pipe, assigning the previous left part to the left node and the right part to the next command
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node)
 */

/* prototype */
t_astnode	*parse(t_token *tokens);
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token);
void	add_arg_node(t_astnode *command_node, t_astnode *arg_node);
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token);
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node);


