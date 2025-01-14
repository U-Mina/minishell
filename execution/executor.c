/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 12:39:10 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//*BIG CHANGE* to check and get fd from redir before run any command!!!
//think properly how to proceed. This is just a copy of the logic of AST printing, that should be adapted to executing
//travels the whole AST starting from the AST_root and redirects to the corresponding function to execute each of the types of nodes
void exec_from_top(t_astnode *astnode)
{
	if (handle_redir_fd(astnode, astnode->node_type.cmd->exit_status) == -1)
		return ;
	if (astnode->node_type.cmd->argv && astnode->node_type.cmd->argv[0] == NULL)
	{
		free(astnode->node_type.cmd->argv);
		astnode->node_type.cmd->argv == NULL;
	}
	if (astnode->node_type.cmd->argv && astnode->node_type.cmd->argv[0])
	{
		if (astnode->token->type == COMMAND_BUILTIN)
			exec_builtins(astnode);
		else if (astnode->token->type == COMMAND_BINARY)
		{
			get_path(astnode, astnode->node_type.cmd->exit_status);
			child_proc(astnode, astnode->node_type.cmd->exit_status);
		}
		else
		{
			print_err("minishell", astnode->token->value, "command not found");
			astnode->node_type.cmd->exit_status = 1;
			return ;
		}
	}
}

void child_proc(t_astnode *astnode, int *exit_status)
{
	pid_t pid;
	char **env;
	char **arg;

	env = astnode->node_type.cmd->env;
	arg = astnode->node_type.cmd->argv;
	if (!env)
		return ;
	pid = fork ();
	if (pid == -1)
	{
		print_err("fork", NULL, strerror(errno));
		*exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		//signal()??
		execv(astnode->node_type.cmd->path, arg);
	}
	waitpid(pid, exit_status, 0);
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