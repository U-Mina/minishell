/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/08 12:49:53 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 11:18:08 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parser (syntactic analysis): builds an Abstract Syntax Tree (AST) using recursive descent parsing, and returns a pointer to AST root. The AST has the tokens as nodes, already correctly classified, and hierarchized.
int	parse(t_token *tokens, t_data *data)
{
	int	curr_tok;

	curr_tok = 0;
	data->ast_root = NULL;
	while (tokens && tokens[curr_tok].type != TOKEN_EOF)
	{
		if (tokens[curr_tok].type == WORD || \
			tokens[curr_tok].type == REDIRECTION)
			data->ast_root = parse_cmd(tokens, &curr_tok, data);
		if (tokens[curr_tok].type == PIPE)
			data->ast_root = parse_pipe(tokens, &curr_tok, \
														data->ast_root, data);
		if (!data->ast_root)
			break ;
	}
	if (data->ast_root == NULL && data->malloc_err == false)
	{
		data->exit_status = 258;
		perror("minishell: syntax error");
		return (0);
	}
	else if (data->malloc_err == true)
		return (0);
	return (1);
}
