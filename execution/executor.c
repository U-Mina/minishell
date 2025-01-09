/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/09 13:46:47 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//think properly how to proceed. This is just a copy of the logic of AST printing, that should be adapted to executing
void	exec_ast(t_astnode *ast_node)
//exec_ast(t_astnode *ast_node, int *exit_status)
{
	if (ast_node->token->type == PIPE || ast_node->token->type == REDIRECTION)
	// if (PIPE) -> exec_pip(node, exit_status) **
	//if (REDIR) -> exec_redir(astnode, exit_status)
	{
		create_pipe(ast_node);
	}
	if (ast_node->token->type == COMMAND_BINARY || ast_node->token->type == COMMAND_BUILTIN)
	{
		//if (BIN) -> execve (search path)
		//if (BUIL) -> case_match (direct to seperate) **
		//search in paths etc or in the same files and execute the command
		while (ast_node->next_arg)
		{
			//take argument somehow
			ast_node = ast_node->next_arg;
		}
	}
}

void	create_pipe(t_astnode *pipe_node)
{
	int		fd[2];
	char	buffer[size?!];//which size to give to the pipe buffer?

	if (pipe(fd) == -1)
	{
		//handle_error(pipe fail);
		exit (1);
	}
	if (fork() == 0) //first child process will perform the left part
	{
		close fd[0];
		dup2(fd[1], STDOUT_FILENO);
		exec_ast(pipe_node->left);
		write(fd[1], ) //how to get the return value and write to pipe??
		close fd[1];
		return ();
	}
	if (fork() == 0) // second child process will perform the right part
	{
		close fd[1];
		dup2(fd[0], STDIN_FILENO);
		exec_ast(pipe_node->right); 
		bytes_read = read(fd[0], buffer, sizeof(buffer)); //how to read the output of parent?
		close fd[0];
	}
	close(fd[0]);
	close(fd[1]);
}
