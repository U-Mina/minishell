/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/28 18:49:27 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_signal = 0;

//include all allocated elements in gc_list (using gc_malloc and handle mallocated in other functions ex. ft_split)
//todo: char **envp need to be passed as para in main to get the env from sys 
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_data		data;
	t_minishell	minishell;

	init_minishell(&minishell, ac, av);
	init_data(envp, &data, &minishell);
	while (1)
	{
		input = readline("Minishell>");
		if(!input)
			break ;
		if (*input != '\0' && *gc_strtrim(input, " \t\n\v\f\r") != '\0')
		{
			add_history(input);
			if (g_signal == SIGINT)
			{
				data.exit_status = 1;
				g_signal = 0;
			}
			data.tokens = tokenizer(input);
			//print_tokens(data.tokens); //check lexer
			if (parse(data.tokens, &data))
			{
				//print_ast(data.ast_root, 0); //check parser
				exec_ast(data.ast_root, &data);
			}
			reset_data(&data);
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
		if (ast_node->node_type.pipe->left)
			print_ast(ast_node->node_type.pipe->left, level + 1);
		if (ast_node->node_type.pipe->right)
			print_ast(ast_node->node_type.pipe->right, level + 1);
	}
	else if (ast_node->token->type == REDIRECTION)
	{
		printf("%s (%i.%i): %s\n", ast_node->token->value, ast_node->token->type, ast_node->node_type.redir->type, ast_node->node_type.redir->left);
		if (ast_node->node_type.redir->right)
			print_ast(ast_node->node_type.redir->right, level + 1);
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
