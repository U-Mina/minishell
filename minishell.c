/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/10 13:16:16 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_astnode	*ast_root;

	// //Add signal handling
	while (1)
	{
		//Display a prompt when waiting for a new command
		input = readline("Prompt>");
		//Have a working history 
		add_history(input);
		//Split into categorized tokens
		tokens = tokenizer(input);
		free(input);
		//check lexer
		print_tokens(tokens);
		//Create AST with hierarchized tokens
		ast_root = parse(tokens);
		printf("check parse\n");
		//check parser
		print_ast(ast_root, 0);
		//free allocated memory
		free_tokens(&tokens);
		// //execute the command saved into ast
		// //depending on the type of command: 
		// //1. search in files and exec the program
		// //2. create pipe, whatever
		// //3. exec a builtin function
		// exec(command);
	}
	return (0);
}


//COMPROVATIONS
//check lexer
void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_EOF)
	{
		printf("i: %i\ntype: %i\nvalue: %s\n\n", i, tokens[i].type, tokens[i].value);
		i++;
	}
}

//check parser
void	print_ast(t_astnode* ast_node, int level)
{
	int	i;

	printf("%i:	type:%i\n	value: %s\n\n", level, ast_node->token->type, ast_node->token->value);
	if (ast_node->token->type == PIPE || ast_node->token->type == REDIRECTION)
	{
		print_ast(ast_node->left, level++);
		print_ast(ast_node->right, level++);
	}
	else if (ast_node->token->type == COMMAND_BINARY || ast_node->token->type == COMMAND_BUILTIN)
	{
		i = 0;
		while (ast_node->arg_count != 0)
		{
			printf("%i:	type:%i\n	value: %s\n\n", level++, ast_node->arguments[i - 1]->token->type, ast_node->arguments[i - 1]->token->value);
			i++;
			ast_node->arg_count--;
		}
	}
}
