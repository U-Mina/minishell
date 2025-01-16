/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 12:13:30 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//include all allocated elements in gc_list (using gc_malloc and handle mallocated in other functions ex. ft_split)
//todo: char **envp need to be passed as para in main to get the env from sys 
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_token		*tokens;
	t_data		data;
	int			exit_status;
	//t_astnode	*ast_root;
	t_minishell	minishell;

	exit_status = 0;
	init_data(envp, &data, &exit_status);
	init_minishell(&minishell);
	while (1)
	{
		//Display a prompt when waiting for a new command
		input = readline("Prompt>");
		if(!input)
			break ;
		if (*input != '\0')
		{
			add_history(input);
			//Split into categorized tokens
			tokens = tokenizer(input, &exit_status);
			//free(input);//free at the end for all cases
			//check lexer
			print_tokens(tokens);
			//Create AST with hierarchized tokens
			data.ast_root = parse(tokens);
			//check parser
			print_ast(data.ast_root, 0);
			//execution
			//exec_ast(ast_root);
			//free allocated memory
			free_tokens(tokens);
			free_ast(data.ast_root);
			// //execute the command saved into ast
			// //depending on the type of command: 
			// //1. search in files and exec the program
			// //2. create pipe, whatever
			// //3. exec a builtin function
			// exec(command);
		}
		free(input);
		rl_on_new_line();
	}
	term_minishell(&minishell, 0);
	//return (0); //already done in term_minshell!?
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
	int	j;

	i = 0;
	while(i++ < level)
		printf("	");
	if (ast_node->token->type == PIPE)
	{
		printf("%s (%i)\n", ast_node->token->value, ast_node->token->type);
		print_ast(ast_node->node_type.pipe->left, level + 1);
		print_ast(ast_node->node_type.pipe->right, level + 1);
	}
	else if (ast_node->token->type == REDIRECTION)
	{
		printf("%s (%i.%i): %s\n", ast_node->token->value, ast_node->token->type, ast_node->node_type.redirect->type, ast_node->node_type.redirect->left);
		print_ast(ast_node->node_type.redirect->right, level + 1);
	}
	else if (ast_node->token->type == COMMAND)
	{
		printf("%s (%i.%i):\n", ast_node->token->value, ast_node->token->type, ast_node->node_type.cmd->type);
		j = 1;
		while (j <= ast_node->node_type.cmd->arg_nb)
		{
			i = 0;
			while(i < level + 1)
			{
				printf("	");
				i++;
			}
			printf("arg %i: %s\n", j, ast_node->node_type.cmd->argv[j]);
			j++;
		}
	}
}
