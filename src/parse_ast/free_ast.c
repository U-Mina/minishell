/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 17:25:37 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 18:20:00 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to use after tokens have been used. Frees each allocated value in the token structure array and frees the whole array
void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_EOF)
	{
		gc_free(tokens[i].value);
		i++;
	}
	gc_free(tokens);
}

//in libft or in helpers
//frees all the string elements in a double pointer, and the double pointer itself
void	free_double_pointer(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		gc_free(str[i]);
		i++;
	}
	gc_free(str);
}

void	free_ast(t_astnode *ast_node)
{
	if (ast_node->token->type == PIPE)
	{
		free_ast(ast_node->node_type.pipe->left);
		free_ast(ast_node->node_type.pipe->right);
	}
	else if (ast_node->token->type == REDIRECTION)
	{
		gc_free(ast_node->node_type.redir->left);
		free_ast(ast_node->node_type.redir->right);
	}
	else if (ast_node->token->type == COMMAND)
	{
		if (ast_node->node_type.cmd->argv)
			free_double_pointer(ast_node->node_type.cmd->argv);
		if (ast_node->node_type.cmd->path)
			gc_free(ast_node->node_type.cmd->path);
		if (ast_node->node_type.cmd->env)
			free_double_pointer(ast_node->node_type.cmd->env);
		gc_free(ast_node->node_type.cmd->exit_status); //not sure if we need to free this or is the same as in main!!!!????
	}
	// gc_free(ast_node->fd);//??
	gc_free(ast_node);
}
