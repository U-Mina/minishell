/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:03:59 by ewu               #+#    #+#             */
/*   Updated: 2025/01/15 13:52:51 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * - create pipi
 * - redirct and connect pipe
 * - close and clean
 */

//to do fork_err() or just print_err()?
static pid_t fork_err(pid_t id, int fd[2], int *exit_status)
{
	id = fork();
	if (id < 0)
	{
		print_err("fork", NULL, strerror(errno));
		*exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		exit(*exit_status);
	}
	return (id);
}

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

int left_node(t_astnode *astnode, int fd[2], int *exit_status)
{
	pid_t left;

	left = fork_err(left, fd, exit_status);
	if (left == -1)
		return -1;
	if (left == 0)
	{
		cloe(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		exec_ast(astnode, exit_status);
		//maybe while loop is better than recursion**
//now: pass pipe_node, and specify in exec_pipe 
//or specify here exec_ast(pipe_node->left, exit_status); 
		exit(*exit_status);
	}
	return (left);
}

int right_node(t_astnode *astnode, int fd[2], int *exit_status)
{
	pid_t right;

	right = fork_err(right, fd, exit_status);
	if (right == -1)
		return -1;
	if (right == 0)
	{
		cloe(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		exec_ast(astnode, exit_status);
		exit(*exit_status);
	}
	return (right);
}

void exec_pipe(t_data *data)
{
	int fd[2];
	pid_t left;
	pid_t right;
	t_pipe *p_node;
	
	p_node = data->ast_root->node_type.pipe;
	if (create_pip(fd, data->exit_status) < 0)
		return ;
	left = left_node(p_node->left, fd, data->exit_status);
	if (left < 0)
		return ;
	right = right_node(p_node->right, fd, data->exit_status);
	if (right < 0)
		return ;
	close(fd[0]);
	close(fd[1]);
	waitpid(left, data->exit_status, 0);
	waitpid(right, data->exit_status, 0);
	exit (data->exit_status);
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
