/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:32:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 12:06:43 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PENDING: right and left or others according to what is ued in redirect_execution

//parses redirection when present, creating a redirection node, being the left node the command node and the right node the filename
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token, t_gc_list *gc_list)
{
	t_astnode	*redirection_node;
	t_astnode	*child_node;

	redirection_node = create_astnode(&tokens[*current_token], gc_list);
	redirection_node->node_type.redirect->type = get_redir_type(tokens[*current_token].value);
	child_node = NULL;
	if (!redirection_node)
		return (handle_error(gc_list));
	redirection_node->left = command_node;
	(*current_token)++;
	if (tokens[*current_token].type == WORD)
	{
		tokens[*current_token].type = FILENAME;
		if (tokens[*current_token - 1].type == HEREDOC)
			tokens[*current_token].type = DELIMITER;
		child_node = create_astnode(&tokens[*current_token], gc_list);
		if (!child_node)
			return (handle_error(gc_list));
		redirection_node->right = child_node;
		(*current_token)++;
	}
	return (redirection_node);
}

//disambiguates the tokentype, being a redirection (in, out, append or heredoc)
t_tokentype	get_redir_type(char *redir)
{
	t_tokentype	redir_type;

	if (ft_strncmp(redir, "<") == 0)
		redir_type = INPUT;
	if (ft_strncmp(redir, ">") == 0)
		redir_type = OUTPUT;
	if (ft_strncmp(redir, "<<") == 0)
		redir_type = HEREDOC;
	if (ft_strncmp(redir, ">>") == 0)
		redir_type = APPEND;
	return (redir_type);
}
