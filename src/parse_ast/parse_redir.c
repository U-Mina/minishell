/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:32:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 12:01:52 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//parses redirection when present, creating a redirection node, being the left node the filename or the delimiter and the left node the command node or redirections to be further executed
t_astnode	*parse_redir(t_token *tokens, int *curr_tok, t_astnode *right_node)
{
	t_astnode	*redir_node;

	redir_node = create_astnode(&tokens[*curr_tok]);
	redir_node->node_type.redir->type = get_redir_type(tokens[*curr_tok].value);
	// if (!redir_node)
	// 	return (handle_error(gc_list));
	(*curr_tok)++;
	if (tokens[*curr_tok].type == WORD || \
		tokens[*curr_tok].type == QUOTE)
	{
		redir_node->node_type.redir->left = tokens[*curr_tok].value;
		(*curr_tok)++;
		if (tokens[*curr_tok].type == REDIRECTION)
			redir_node->node_type.redir->right = \
			parse_redir(tokens, curr_tok, right_node);
		else
			redir_node->node_type.redir->right = right_node;
	}
	return (redir_node);
}

//disambiguates the tokentype, being a redirection (in, out, append or heredoc)
t_redirtype	get_redir_type(char *redir)
{
	t_redirtype	redir_type;

	if (ft_strncmp(redir, "<", 2) == 0)
		redir_type = INPUT;
	if (ft_strncmp(redir, ">", 2) == 0)
		redir_type = OUTPUT;
	if (ft_strncmp(redir, "<<", 3) == 0)
		redir_type = HEREDOC;
	if (ft_strncmp(redir, ">>", 3) == 0)
		redir_type = APPEND;
	return (redir_type);
}
