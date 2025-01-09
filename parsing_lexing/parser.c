/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:49:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/09 10:19:48 by ipuig-pa         ###   ########.fr       */
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
t_astnode	*parse(t_token *tokens, t_gc_list *gc_list)
{
	t_astnode	*root;
	char		**builtins;
	int			current_token;

	builtins = check_builtins(gc_list);
	current_token = 0;
	root = parse_command(tokens, builtins, &current_token, gc_list);
	while (tokens[current_token].type != TOKEN_EOF)
	{
		if (tokens[current_token].type == PIPE)
			root = parse_pipe(tokens, builtins, &current_token, root, gc_list);
	}
	free_double_pointer(builtins);
	return (root);
}

//creates AST nodes for commands and their descending nodes arguments
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token, t_gc_list *gc_list)
{
	t_astnode	*command_node;
	t_astnode	*arg_node;

	command_node = NULL;
	arg_node = NULL;
	if (tokens[*current_token].type == WORD)
	{
		tokens[*current_token].type = get_command_type(tokens[*current_token].value, builtins);
		command_node = create_astnode(&tokens[*current_token], gc_list);
		if (!command_node)
			handle_error(gc_list);
		(*current_token)++;
		while (tokens[*current_token].type == WORD || tokens[*current_token].type == QUOTE)
		{
			tokens[*current_token].type = ARGUMENT;
			arg_node = create_astnode(&tokens[*current_token], gc_list);
			if (!arg_node)
				handle_error(gc_list);
			add_arg_node(command_node, arg_node);
			(*current_token)++;
		}
		if (tokens[*current_token].type == REDIRECTION)
			return (parse_redirection(tokens, command_node, current_token, gc_list));
	}
	return (command_node);
}

//adds an argument node as part of the children nodes of a command node
void	add_arg_node(t_astnode *command_node, t_astnode *arg_node)
{
	t_astnode	*last_arg;

	last_arg = command_node;
	while (last_arg->next_arg)
		last_arg = last_arg->next_arg;
	last_arg->next_arg = arg_node;
	command_node->args_nbr++;
}

//parses redirection when present, creating a redirection node, being the left node the command node and the right node the filename
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token, t_gc_list *gc_list)
{
	t_astnode	*redirection_node;
	t_astnode	*file_node;

	redirection_node = create_astnode(&tokens[*current_token], gc_list);
	file_node = NULL;
	if (!redirection_node)
		handle_error(gc_list);
	redirection_node->left = command_node;
	(*current_token)++;
	if (tokens[*current_token].type == WORD)
	{
		tokens[*current_token].type = FILENAME;
		file_node = create_astnode(&tokens[*current_token], gc_list);
		if (!file_node)
			handle_error(gc_list);
		redirection_node->right = file_node;
		(*current_token)++;
	}
	return (redirection_node);
}

//parses the pipe, assigning the previous left part to the left node and the right part to the next command
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node, t_gc_list *gc_list)
{
	t_astnode	*pipe_node;

	if (tokens[*current_token].type == PIPE)
	{
		pipe_node = create_astnode(&tokens[*current_token], gc_list);
		(*current_token)++;
		pipe_node->left = left_node;
		pipe_node->right = parse_command(tokens, builtins, current_token, gc_list);
		return (pipe_node);
	}
	else
		return (left_node);
}

//creates a new node for the AST (Abstract Syntax Tree)
t_astnode	*create_astnode(t_token *token, t_gc_list *gc_list)
{
	t_astnode	*new_node;

	new_node = (t_astnode *)gc_malloc(sizeof(t_astnode), gc_list);
	if (!new_node)
		handle_error(gc_list);
	new_node->token = token;
	if (new_node->token->type == PIPE || new_node->token->type == REDIRECTION)
	{
		new_node->right = NULL;
		new_node->left = NULL;
	}
	else
	{
		new_node->next_arg = NULL;
		new_node->args_nbr = 0;
	}
	return (new_node);
}

//find a better way to create the array of strings accessible here?
//disambiguates the tokentype, being a command (binary or builtin)
t_tokentype	get_command_type(char *command, char **builtins)
{
	t_tokentype	command_type;
	int			i;

	command_type = COMMAND_BINARY;
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(command, builtins[i], ft_strlen(command)) == 0)
		{
			command_type = COMMAND_BUILTIN;
			break ;
		}
		else
			i++;
	}
	return (command_type);
}

//creates an array of strings, each being one of the possible implemented builtins
char	**check_builtins(t_gc_list *gc_list)
{
	char	**builtins;

	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	if (!builtins)
		handle_error(gc_list);
	return (builtins);
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