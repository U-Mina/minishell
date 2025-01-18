/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 20:28:11 by ewu               #+#    #+#             */
/*   Updated: 2025/01/18 16:31:25 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	dup_err(int fd1, int std_fd, int *exit_status)
{
	int	res;

	res = dup2(fd1, std_fd);
	if (res == -1)
	{
		print_err("dup2", NULL, strerror(errno));
		*exit_status = 1;
		return (-1);
	}
	*exit_status = 0;
	return (0);
}

static int	update_fd(t_data *data)
{
	if (data->fd[0] != 0) //being overwrite by new_fd, change with stdin
	{
		if (dup_err(data->fd[0], STDIN_FILENO, &data->exit_status) == -1)//stdin_fileno
			return (-1);
		close(data->fd[0]);
	}
	if (data->fd[1] != 1)
	{
		if (dup_err(data->fd[1], STDOUT_FILENO, &data->exit_status) == -1)//stdout_fileno
			return (-1);
		close(data->fd[1]);
	}
	data->exit_status = 0;
	return (0);
}

int	exec_redir(t_redir *redir, t_data *data)
{
	if (redir->type == HEREDOC)
	{
		exec_heredoc(redir->left, &data->exit_status, data);
		if (data->heredoc_fd < 0)
			return (-1);
	}
	else if (redir->type == INPUT)
	{
		if (exec_in(redir, data) < 0)
			return (-1);
	}
	else if (redir->type == OUTPUT || redir -> type == APPEND)
	{
		if (exec_out(redir, data) < 0)
			return (-1);
	}
	if (!update_fd(data))//proper error handling
	{
		data->exit_status = 0;
		exec_ast(redir->right, data);
		return (0);
	}
	return (-1);
}


// //todo: ft handle_redir(), this ft will do error_check for fd(<0?) and clean and direct to exec_redir
// /**
//  * typedef struct s_redir
// {
// 	t_redirtype			type;
// 	int					fd;
// 	char				*left;
// 	struct s_astnode	*right;
// }				t_redir;
// typedef struct s_token
// {
// 	t_tokentype			type;
// 	char				*value;
// }						t_token;
// typedef struct s_astnode
// {
// 	t_token		*token;
// 	t_nodetype	node_type;
// }				t_astnode;
//  */

// //heredoc_fd is specially for heredoc<<
// //heredoc need a tmp fd to hold the content, and then call dup2(heredoc_fd, STDIN_FILENO(0))
// int	check_redir(t_redir *redir, t_data *data)
// {
// 	while (redir)
// 	{
// 		if (redir->type == HEREDOC)
// 		{
// 			redir->heredoc_fd = here_doc(redir->left, data->exit_status); //redir->token->value shouc be change to redir->right->token->value ???
// 			if (redir->heredoc_fd < 0)
// 				return (-1);
// 		}
// 		redir = redir->right->node_type.redir;
// 	}
// 	if (ft_in(redir, data) < 0 || ft_out(redir, data) < 0)
// 		return (-1);
// 	return (0);
// }


// int	handle_redir_fd(t_redir *redir, t_data *data)
// {
// 	if (redir)
// 	{
// 		if (check_redir(redir, data) == -1)
// 			return -1;
// 		if (data->fd[0] != 0) //being overwrite by new_fd, change with stdin
// 		{
// 			if (dup_err(data->fd[0], 0, data->exit_status) == -1)//stdin_fileno
// 				return (-1);
// 			close(data->fd[0]);
// 		}
// 		if (data->fd[1] != 1)
// 		{
// 			if (dup_err(data->fd[1], 1, data->exit_status) == -1)//stdout_fileno
// 				return (-1);
// 			close(data->fd[1]);
// 		}
// 	}
// 	*(data->exit_status) = 0;
// 	return (0);
// }

// static void child_redir(t_astnode *astnode, int *exit_status)
// {
// 	pid_t pid;
// 	char **env;
// 	char **arg;

// 	env = astnode->node_type.cmd->env;
// 	arg = astnode->node_type.cmd->argv;
// 	if (!env)
// 		return ;
// 	pid = fork ();
// 	if (pid == -1)
// 	{
// 		print_err("fork", NULL, strerror(errno));
// 		*exit_status = 1;
// 		return ;
// 	}
// 	if (pid == 0)
// 	{
// 		//signal()??
// 		execv(astnode->node_type.cmd->path, arg);
// 	}
// 	waitpid(pid, exit_status, 0);
// 	free(env);
// }

// void exec_redir(t_astnode *astnode, int *exit_status)
// {
// //some empty arg/*arg[0] check needed
// //also empty/null cmd??
// 	if (handle_redir_fd(astnode, exit_status) == -1)
// 		return ;
// 	if (astnode->node_type.cmd->argv && astnode->node_type.cmd->argv[0] == NULL)
// 	//the cmd (argv[0]) is NULL
// 	{
// 		free(astnode->node_type.cmd->argv);
// 		astnode->node_type.cmd->argv == NULL;
// 	}
// 	if (astnode->node_type.cmd->argv && astnode->node_type.cmd->argv[0])
// 	{
// 		if (astnode->token->type == COMMAND_BUILTIN)
// 			exec_builtins(astnode, exit_status);
// 		else if (astnode->token->type == COMMAND_BINARY)
// 		{
// 			get_path(astnode, exit_status);
// 			child_redir(astnode, exit_status);
// 		}
// 	}
// }

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
