/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:28:11 by ewu               #+#    #+#             */
/*   Updated: 2025/01/10 13:52:00 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/minishell.h"

//todo: ft handle_redir(), this ft will do error_check for fd(<0?) and clean and direct to exec_redir

/* redirection_node: retval of @fn: t_astnode *parse_redirection*/
int exec_redirect(t_astnode *astnode, int *exit_status)
{
	t_redir *redir;

	redir = astnode->redirect;
	while (redir)
	{
		if (redir->token->type == HEREDOC)
		{
			redir->fd = here_doc(redir->token->value, exit_status); //redir->token->value shouc be change to redir->right->token->value ???
			if (redir->fd < 0)
				return -1;
		}
		redir = redir->right;
	}
	if (in_output(astnode, exit_status) < 0)
		return -1;
	return 0;
}

int in_output(t_astnode *astnode, int *exit_status)
{
	if (ft_in(astnode, exit_status) < 0 || ft_out(astnode, exit_status) < 0)
		return -1;
	return 0;
}

	// if (redir)
	// {
	// 	*exit_status = 1;
	// 	print_err("minishell", NULL, "missing filename for redirection");
	// 	return (-1);
	// }
	// if (redirection_node->token->type == INPUT)
	// 	fd = open();
	// else if (redirection_node->token->type == OUTPUT)
	// 	fd = open();
	// else if (redirection_node->token->type == APPEND)
	// 	fd = open ();
	// else
	// 	{
	// 		*exit_status = 1;
	// 		print_err("minishell", NULL, "unsupported redirection type");
	// 		return (-1);		
	// 	}