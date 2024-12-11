/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/11 12:56:20 by ipuig-pa         ###   ########.fr       */
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
		//check parser
		print_ast(ast_root, 0);
		//execution
		//exec_ast(ast_root);
		//free allocated memory
		free_tokens(&tokens);
		//pending of free ast

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
	int		i;

	i = 0;
	while(i++ < level)
		printf("	");
	printf("%s (%i)\n", ast_node->token->value, ast_node->token->type);
	if (ast_node->token->type == PIPE || ast_node->token->type == REDIRECTION)
	{
		print_ast(ast_node->left, level + 1);
		print_ast(ast_node->right, level + 1);
	}
	else if (ast_node->token->type == COMMAND_BINARY || ast_node->token->type == COMMAND_BUILTIN)
	{
		while (ast_node->next_arg)
		{
			i = 0;
			while(i < level + 1)
			{
				printf("	");
				i++;
			}
			printf("%s (%i)\n", ast_node->next_arg->token->value, ast_node->next_arg->token->type);
			ast_node = ast_node->next_arg;
		}
	}
}
