/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 17:26:13 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_data		data;

	init(envp, &data, ac, av);
	while (1)
	{
		input = readline("Minishell>");
		if (!input)
			return (exit_eof(&(data.minishell)), 0);
		if (*input != '\0' && *gc_strtrim(input, " \t\n\v\f\r") != '\0')
		{
			add_history(input);
			reset_signal(&data);
			if (!tokenizer(input, &data))
				data.exit_status = 1;
			else if (parse(data.tokens, &data))
				executor(&data);
			reset_data(&data);
		}
		free(input);
		rl_on_new_line();
	}
	return (term_minishell(&(data.minishell), 0), 0);
}

// //CHANGE THIS CHUNK FOR AST CHECKING
// else if (parse(data.tokens, &data))
// {
// 	//print_tokens(data.tokens); //check lexer
// 	//print_ast(data.ast_root, 0); //check parser
// 	executor(&data);
// }
// reset_data(&data);

// //COMPROVATIONS
// //check lexer
// void	print_tokens(t_token *tokens)
// {
// 	int	i;

// 	i = 0;
// 	while (tokens[i].type != TOKEN_EOF)
// 	{
// 		printf("i: %i\ntype: %i\nvalue: %s\n\n", i, tokens[i].type, \
// 				tokens[i].value);
// 		i++;
// 	}
// }

// //check parser
// void	print_ast(t_astnode* ast_node, int level)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i++ < level)
// 		printf("	");
// 	if (ast_node->token->type == PIPE)
// 	{
// 		printf("%s (%i)\n", ast_node->token->value, ast_node->token->type);
// 		if (ast_node->node_type.pipe->left)
// 			print_ast(ast_node->node_type.pipe->left, level + 1);
// 		if (ast_node->node_type.pipe->right)
// 			print_ast(ast_node->node_type.pipe->right, level + 1);
// 	}
// 	else if (ast_node->token->type == REDIRECTION)
// 	{
// 		printf("%s (%i.%i): %s\n", ast_node->token->value, \
// 		ast_node->token->type, ast_node->node_type.redir->type, \
// 		ast_node->node_type.redir->left);
// 		if (ast_node->node_type.redir->right)
// 			print_ast(ast_node->node_type.redir->right, level + 1);
// 	}
// 	else if (ast_node->token->type == COMMAND)
// 	{
// 		printf("%s (%i.%i):\n", ast_node->token->value, \
// 		ast_node->token->type, \
// 		ast_node->node_type.cmd->type);
// 		j = 1;
// 		while (j <= ast_node->node_type.cmd->arg_nb)
// 		{
// 			i = 0;
// 			while (i < level + 1)
// 			{
// 				printf("	");
// 				i++;
// 			}
// 			printf("arg %i: %s\n", j, ast_node->node_type.cmd->argv[j]);
// 			j++;
// 		}
// 	}
// }