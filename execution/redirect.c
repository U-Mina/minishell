/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:28:11 by ewu               #+#    #+#             */
/*   Updated: 2025/01/12 16:17:30 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//todo: ft handle_redir(), this ft will do error_check for fd(<0?) and clean and direct to exec_redir
/**
 * typedef struct s_redir
{
	t_redirtype			type;
	int					fd;
	char				*left;
	struct s_astnode	*right;
}				t_redir;
typedef struct s_token
{
	t_tokentype			type;
	char				*value;
}						t_token;
typedef struct s_astnode
{
	t_token		*token;
	t_nodetype	node_type;
}				t_astnode;
 */

//heredoc_fd is specially for heredoc<<
//heredoc need a tmp fd to hold the content, and then call dup2(heredoc_fd, STDIN_FILENO(0))
int check_redir(t_astnode *astnode, int *exit_status)
{
	t_redir *redir;

	redir = astnode->node_type.redir;
	while (redir)
	{
		if (redir->type == HEREDOC)
		{
			redir->heredoc_fd = here_doc(redir->left, exit_status); //redir->token->value shouc be change to redir->right->token->value ???
			if (redir->heredoc_fd < 0)
				return -1;
		}
		redir = redir->right->node_type.redir;
	}
	if (ft_in(astnode, exit_status) < 0 || ft_out(astnode, exit_status) < 0)
		return -1;
	return 0;
}

static int dup_err(int fd1, int std_fd, int *exit_status)
{
	int res;

	res = dup2(fd1, std_fd);
	if (res == -1)
	{
		print_err("dup2", NULL, strerror(errno));
		*exit_status = 1;
		return -1;
	}
	*exit_status = 0;
	return 0;
}

int handle_redir_fd(t_astnode *astnode, int *exit_status)
{
	t_redir *redir;

	redir = astnode->node_type.redir;
	if (redir)
	{
		if (check_redir(astnode, exit_status) == -1)
			return -1;
		if (astnode->fd[0] != 0) //being overwrite by new_fd, change with stdin
		{
			if (dup_err(astnode->fd[0], 0, exit_status) == -1)//stdin_fileno
				return -1;
			close(astnode->fd[0]);
		}
		if (astnode->fd[1] != 1)
		{
			if (dup_err(astnode->fd[1], 1, exit_status) == -1)//stdout_fileno
				return -1;
			close(astnode->fd[1]);	
		}
	}
	*exit_status = 0;
	return 0;
}

int exec_redir(t_astnode *astnode, int *exit_status)
{
	if (handle_redir_fd(astnode, exit_status) == -1)
		return -1;
	if (astnode->token->type == COMMAND_BUILTIN)
		exec_builtins();
	else if (astnode->token->type == COMMAND_BINARY)
	{
		child();
		{//inside child()
			find_path();
			fork();
			if (pid == 0)
			{
				signal(), exeve(path, arg, env)
			}
		}
	}
}





// int in_output(t_astnode *astnode, int *exit_status)
// {
// 	if (ft_in(astnode, exit_status) < 0 || ft_out(astnode, exit_status) < 0)
// 		return -1;
// 	return 0;
// }
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
