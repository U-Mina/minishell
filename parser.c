/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:49:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/09 17:41:55 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.c"

//TO MOVE TO HEADER FILE
typedef struct s_astnode
{
	t_token		*token;
	t_astnode	*right;
	t_astnode	*left;
}	t_astnode;


//parser (syntactic analysis): builds an Abstract Syntax Tree (AST) using recursive descent parsing, and returns a pointer to AST root. The AST has the tokens as nodes, already correctly classified, and hierarchized.
t_astnode	*parse(t_token *tokens)
{
	t_astnode	root;
	char		**builtins;

	builtins = check_builtins();
	root = parse_pipe(tokens, builtins);
	return (root);
}

t_astnode parse_pipe(tokens, builtins)
{
	left_command = parse_command
	if (pipe)
		create pipe node
		process right command = parse_command
		return (pipe node)
	else
		return (left_node);
}

//creates AST nodes for commands and their descending nodes arguments
t_astnode	*parse_command(t_token *tokens, char **builtins)
{
	t_astnode	*command_node;

	if (tokens->type == WORD)
	{
		token->type = get_command_type(tokens->value, builtins);
		command_node = create_astnode(tokens);
		tokens++;
		while (tokens->type == WORD)
		{
			token->type = ARGUMENT;
			//include each argument as a children node of command
			command_node->child= create_astnode()
			tokens++;
		}
		if (tokens->type == REDIRECTION)
			parse_redirection(); --> right part will be a destination file (environmental variables?!?!)
			include command as left part of redirection
			return (redirection_node);
	}
	return (command_node);
}

//creates a new node for the AST (Abstract Syntax Tree)
t_astnode	*create_astnode(t_token *token)
{
	t_astnode	new_node;

	new_node.token = token;
	new_node.right = NULL;
	new_node.left = NULL;
}

//find a better way to create the array of strings accessible here (maybe somewhere defined in the main that can be passed here)
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
	free_double_pointer(builtins);
	return (command_type);
}

//creates an array of strings, each being one of the possible implemented builtins
char	**check_builtins(void)
{
	char	**builtins;

	builtins = ft_split("echo cd pwd export unset env exit", ' ');
	// if (!builtins)
	// 	handle_error(memory alloc fail);
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
