/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 13:12:18 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_at_top(t_data *data)
{
	if (data == NULL || data->ast_root == NULL)
		return ;
	if (data->ast_root->token->type == PIPE)//single cmd, no pipe
		exec_with_pipe(data);
	else
		exec_after_top(data);
	//clean and free function needed to clean 'data'??
}

void exec_with_pipe(t_data *data)
{
	exec_pipe(data);
	if (data->ast_root && data->ast_root->token->type != PIPE)
		exec_after_top(data);
}

//*BIG CHANGE* to check and get fd from redir before run any command!!!
//think properly how to proceed. This is just a copy of the logic of AST printing, that should be adapted to executing
//travels the whole AST starting from the AST_root and redirects to the corresponding function to execute each of the types of nodes
void exec_after_top(t_data *data)
{
	// if (data->ast_root->token->type == PIPE)
	// 	exec_pipe(data);
	if (handle_redir_fd(data) == -1)
		return ;
	if (data->ast_root->node_type.cmd->argv && data->ast_root->node_type.cmd->argv[0] == NULL)
	{
		gc_free(data->ast_root->node_type.cmd->argv);
		data->ast_root->node_type.cmd->argv = NULL;
	}
	if (data->ast_root->node_type.cmd->argv && data->ast_root->node_type.cmd->argv[0])
	{
		if (data->ast_root->token->type == COMMAND_BUILTIN)
			exec_builtins(data);
		else if (data->ast_root->token->type == COMMAND_BINARY)
		{
			get_path(data);
			child_proc(data);
		}
		else
		{
			print_err("minishell", data->ast_root->token->value, "command not found");
			*(data->ast_root->node_type.cmd->exit_status) = 1;
			return ;
		}
	}
}

void child_proc(t_data *data)
{
	pid_t pid;
	char **env;
	char **arg;

	env = data->ast_root->node_type.cmd->env;
	arg = data->ast_root->node_type.cmd->argv;
	if (!env)
		return ;
	pid = fork ();
	if (pid == -1)
	{
		print_err("fork", NULL, strerror(errno));
		*(data->exit_status) = 1;
		return ;
	}
	if (pid == 0)
	{
		//signal()??
		execv(data->ast_root->node_type.cmd->path, arg);
	}
	waitpid(pid, data->exit_status, 0);
	free(env);
}

// void	exec_ast(t_astnode *ast_node, int *exit_status)
// {
// 	if (ast_node->token->type == PIPE)
// 		exec_pip(ast_node, exit_status);
// 	else if (ast_node->token->type == REDIRECTION) //have into account or distinguish between INPUT, OUTPUT, HEREDOC and APPEND
// 		exec_redir(ast_node, exit_status);
// 	else if (ast_node->token->type == COMMAND_BUILTIN)
// 		exec_builtins(ast_node, exit_status);
// 		//case_match(get_command_args(ast_node)); //(direct to seperate) **
// 	else if (ast_node->token->type == COMMAND_BINARY)
// 	{
// 		get_path(ast_node, exit_status);
// 		execve(ast_node->node_type.cmd->path, ast_node->node_type.cmd->argv);//adjust env to wherever it is
// 	}
// }