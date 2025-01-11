/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 15:39:09 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//include all allocated elements in gc_list (using gc_malloc and handle mallocated in other functions ex. ft_split)
//todo: char **envp need to be passed as para in main to get the env from sys 
int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_astnode	*ast_root;

	//Add signal handling
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
		free_tokens(tokens);
		//pending of free ast
		// //execute the command saved into ast
		// //depending on the type of command: 
		// //1. search in files and exec the program
		// //2. create pipe, whatever
		// //3. exec a builtin function
		// exec(command);
	}
	gc_clean();
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

/** init and pass env to t_cmd */
void init_env(char **envp, t_cmd *cmd, int *exit_status)
{
	if (!envp[0])
	{
		cmd->env = create_env();
		if (cmd->env == NULL)
		{
			*exit_status = 1;
			exit(1);			
		}
	}
	else
	{
		cmd->env = cpy_env(envp);
		if (cmd->env == NULL)
		{
			*exit_status = 1;
			exit(1);			
		}
		change_shlvl_oldpwd(&cmd->env, "SHLVL", "OLDPWD");
	}
}
