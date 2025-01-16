/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:31:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 12:01:39 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parses the pipe, assigning the previous left part to the left node and the right part to the next command
t_astnode	*parse_pipe(t_token *tokens, int *curr_tok, t_astnode *left_node)
{
	t_astnode	*pipe_node;
	t_pipe		*pipe;

	if (tokens[*curr_tok].type == PIPE)
	{
		pipe_node = create_astnode(&tokens[*curr_tok]);
		// if (!pipe_node)
		// 	return (handle_error(gc_list));
		(*curr_tok)++;
		pipe = pipe_node->node_type.pipe;
		pipe->left = left_node;
		pipe->right = parse_cmd(tokens, curr_tok);
		return (pipe_node);
	}
	else
		return (left_node);
}
