/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:45:57 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/31 10:45:10 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//think properly how to proceed. This is just a copy of the logic of AST printing, that should be adapted to executing
void	exec_ast(t_astnode *ast_node)
{
	if (ast_node->token->type == PIPE || ast_node->token->type == REDIRECTION)
	{
		create_pipe(ast_node);
	}
	if (ast_node->token->type == COMMAND_BINARY || ast_node->token->type == COMMAND_BUILTIN)
	{
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
	pid_t	pid;
	char	buffer[size?!];//which size to give to the pipe buffer?

	if (pipe(f) == -1)
	{
		//handle_error(pipe fail);
		exit (1);
	}
	pid = fork();
	if (pid < 0)
	{
		//handle_error(fork fail);
		exit (1);
	}
	else if (pid > 0) //parent process will perform the left part
	{
		close fd[0];
		exec_ast(pipe_node->left);
		write(fd[1], ) //how to get the return value and write to pipe
		close fd[1];
	}
	else if (pid == 0) // child process will perform the right part
	{
		close fd[1];
		exec_ast(pipe_node->right); 
		bytes_read = read(fd[0], buffer, sizeof(buffer)); //how to read the output of parent?
		close fd[0];
	}
}
