/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:03:59 by ewu               #+#    #+#             */
/*   Updated: 2025/01/09 14:02:00 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * - create pipi
 * - redirct and connect pipe
 * - close and clean
//parser (syntactic analysis): builds an Abstract Syntax Tree (AST) using recursive descent parsing, and returns a pointer to AST root. The AST has the tokens as nodes, already correctly classified, and hierarchized.
t_astnode	*parse(t_token *tokens)
//creates AST nodes for commands and their descending nodes arguments
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token)
//adds an argument node as part of the children nodes of a command node
void	add_arg_node(t_astnode *command_node, t_astnode *arg_node)
//parses redirection when present, creating a redirection node, being the left node the command node and the right node the filename
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token)
//parses the pipe, assigning the previous left part to the left node and the right part to the next command
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node)
 */

/* prototype */
t_astnode	*parse(t_token *tokens);
t_astnode	*parse_command(t_token *tokens, char **builtins, int *current_token);
void	add_arg_node(t_astnode *command_node, t_astnode *arg_node);
t_astnode	*parse_redirection(t_token *tokens, t_astnode *command_node, int *current_token);
t_astnode	*parse_pipe(t_token *tokens, char **builtins, int *current_token, t_astnode *left_node);

int create_pip(int fd[2], int *exit_status)
{
	int pip;
	
	pip = pipe(fd);
	if (pip == 0)
	{
		*exit_status = 0;
		return 0;
	}
	print_err("pipe", NULL, strerror(errno));
	*exit_status = 1;
	return -1;
}

static int pipe_err(); 
// to do *exit_status assign and perror and close(fd)

int left_node(t_astnode *pipe_node, int fd[2], int *exit_status)
{
	pid_t left;
	
	left = fork();
	if (left == -1)
		pipe_err();
	if (left == 0)
	{
		cloe(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_ast(pipe_node->left, exit_status);
	}

}


int exec_pipe(t_astnode *astnode, int *exit_status)
{
}
}

//too many lines, split into several fts
//copied from executor, maybe it is useful here
// void	create_pipe(t_astnode *pipe_node)
// {
// 	int		fd[2];
// 	char	buffer[size?!];//which size to give to the pipe buffer?

// 	if (pipe(fd) == -1)
// 	{
// 		//handle_error(pipe fail);
// 		exit (1);
// 	}
// 	if (fork() == 0) //first child process will perform the left part
// 	{
// 		close fd[0];
// 		dup2(fd[1], STDOUT_FILENO);
// 		exec_ast(pipe_node->left);
// 		write(fd[1], ) //how to get the return value and write to pipe??
// 		close fd[1];
// 		return ();
// 	}
// 	if (fork() == 0) // second child process will perform the right part
// 	{
// 		close fd[1];
// 		dup2(fd[0], STDIN_FILENO);
// 		exec_ast(pipe_node->right); 
// 		bytes_read = read(fd[0], buffer, sizeof(buffer)); //how to read the output of parent?
// 		close fd[0];
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// }
