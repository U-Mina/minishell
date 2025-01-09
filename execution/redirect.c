/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:28:11 by ewu               #+#    #+#             */
/*   Updated: 2025/01/08 14:19:13 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/minishell.h"

//todo: 0105晚：增加了t_redir结构（包含fd和flag，引用t_astnode结构）

/**
 * typedef enum e_tokentype
{
	REDIRECTION,
	PIPE,
	INPUT,
	OUTPUT,
	FILENAME,
	HEREDOC,
	APPEND
}						t_tokentype;

typedef struct s_token
{
	t_tokentype			type;
	char				*value;
}						t_token;

typedef struct s_astnode
{
	int fd[2];
	t_token				*token;
	struct s_astnode	*right;
	struct s_astnode	*left;
	struct s_astnode	*next_arg;
	t_redir				*redirect
}						t_astnode;

typedef struct s_redir
{
	int					fd;
	t_token				*token;
	t_redir			*right;
	t_redir			*left;

}						t_redir;
 */

/* redirection_node: retval of @fn: t_astnode *parse_redirection*/
int exec_redirect(t_astnode *astnode, int *exit_status)
{
	t_redir *redir;

	redir = astnode->redirect;
	while (redir)
	{
		if (redir->token->type == HEREDOC)
		{
			redir->fd = here_doc(redir->token->value, exit_status);
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