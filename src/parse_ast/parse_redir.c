/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:32:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/26 13:16:14 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//disambiguates the tokentype, being a redirection (in, out, append or heredoc)
static t_redirtype	get_redir_type(char *redir)
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

static int	handle_redir_extras(t_token *tokens, int *curr_tok, t_redir *redir,
								t_data *data)
{
	int	h_q;

	if (redir->type != HEREDOC)
	{
		tokens[*curr_tok].value = expand_env(tokens[*curr_tok].value, data);
		if (handle_quotes(&tokens[*curr_tok].value) < 0)
			return (0);
	}
	if (redir->type == HEREDOC)
	{
		h_q = handle_quotes(&tokens[*curr_tok].value);
		if (h_q == 1)
			redir->type = HEREDOC_Q;
		else if (h_q < 0)
			return (0);
	}
	redir->left = tokens[*curr_tok].value;
	(*curr_tok)++;
	return (1);
}

//parses redirection when present, creating a redirection node, being the left node the filename or the delimiter and the left node the command node or redirections to be further executed
t_astnode	*parse_redir(t_token *tokens, int *curr_tok, t_astnode *right_node,
						t_data *data)
{
	t_astnode	*redir_node;
	t_redir		*redir;

	redir_node = NULL;
	if (tokens[*curr_tok].type == REDIRECTION)
	{
		redir_node = create_astnode(&tokens[*curr_tok]);
		redir = redir_node->node_type.redir;
		redir->type = get_redir_type(tokens[*curr_tok].value);
		// if (!redir_node)
		// 	return (handle_error(gc_list));
		if (tokens[++(*curr_tok)].type == WORD)
		{
			if (!handle_redir_extras(tokens, curr_tok, redir, data))
				return (NULL);
		}
		if (right_node == NULL || right_node->token->type != COMMAND)
		{
			if (tokens[*curr_tok].type == WORD)
				redir->right = parse_cmd(tokens, curr_tok, data);
		}
		else
			redir->right = right_node;
	}
	return (redir_node);
}

