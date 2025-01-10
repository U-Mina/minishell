/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:32:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 17:41:07 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PENDING: right and left or others according to what is ued in redirect_execution

//parses redirection when present, creating a redirection node, being the left node the command node and the right node the filename
t_astnode	*parse_redirection(t_token *tokens, int *current_token, t_astnode *left_node, t_gc_list *gc_list)
{
	t_astnode	*redirection_node;

	redirection_node = create_astnode(&tokens[*current_token], gc_list);
	redirection_node->node_type.redirect->type = get_redir_type(tokens[*current_token].value);
	if (!redirection_node)
		return (handle_error(gc_list));
	redirection_node->node_type.redirect->left = left_node;
	(*current_token)++;
	if (tokens[*current_token].type == WORD)
	{
		redirection_node->node_type.redirect->arg = tokens[*current_token].value;
		(*current_token)++;
		if (tokens[*current_token].type == REDIRECTION)
			redirection_node->node_type.redirect->right = parse_redirection(tokens, current_token, redirection_node, gc_list);
	}
	return (redirection_node);
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
