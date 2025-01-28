/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:03:59 by ewu               #+#    #+#             */
/*   Updated: 2025/01/28 19:47:35 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * - create pipi
 * - redirct and connect pipe
 * - close and clean
 */
static pid_t	fork_err(int *fd)
{
	int	id;

	id = fork();
	if (id < 0)
	{
		print_err("fork", NULL, strerror(errno));
		//*exit_status = 1;
		close(fd[0]);
		close(fd[1]);
		return (-1);
		//exit(*exit_status);
	}
	return (id);
}

static int	left_node(t_astnode *ast_node, int *fd, int *sync_fd, t_data *data)
{
	pid_t	left;

	// left = fork_err(fd, &data->exit_status);
	left = fork_err(fd);
	if (left == -1)
		return (data->exit_status = 1, -1);
	if (left == 0)
	{
		close(sync_fd[0]);
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		ast_node = handle_redir_fd(ast_node, data);
		if (g_signal == SIGINT)
		{
			write(sync_fd[1], "sigint", 6);
			close(sync_fd[1]);
			exit(data->exit_status);
		}
		write(sync_fd[1], "done", 4);
		close(sync_fd[1]);
		exec_ast(ast_node, data);
		//maybe while loop is better than recursion**
//now: pass pipe_node, and specify in exec_pipe 
//or specify here exec_ast(pipe_node->left, exit_status);
		exit(data->exit_status);
	}
	return (left);
}

static int	right_node(t_astnode *ast_node, int *fd, int *sync_fd, t_data *data)
{
	pid_t	right;
	char	buffer[7];
	size_t	bytes_read;

	right = fork_err(fd);
	if (right == -1)
		return (data->exit_status = 1, -1);
	if (right == 0)
	{
		signal(SIGINT, SIG_IGN);
		close(sync_fd[1]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		bytes_read = read(sync_fd[0], buffer, 7);
		if (bytes_read == 6 && ft_strncmp(buffer, "sigint", 6) == 0)
			g_signal = SIGINT;
		else if (bytes_read != 4 || ft_strncmp(buffer, "done", 4) != 0)
		{
			perror("Pipe synchronization failed");
			exit(1);
		}
		close(sync_fd[0]);
		restore_signal(data->minishell.sa);
		// ast_node = handle_redir_fd(ast_node, data);//dont know if in the right part is also needed??
		if (g_signal != SIGINT)
		{
			exec_ast(ast_node, data);
			exit(data->exit_status);
		}
		exit(1);
	}
	return (right);
}

// int	create_pipe(int *fd, int *exit_status)
int	create_pipe(int *fd)
{
	int	pip;

	pip = pipe(fd);
	if (pip == 0)
	{
		//*exit_status = 0;
		return (0);
	}
	print_err("pipe", NULL, strerror(errno));
	//*exit_status = 1;
	return (-1);
}

	// if (create_pipe(fd, &data->exit_status) < 0)
	// 	return ;
	// if (create_pipe(sync_fd, &data->exit_status) < 0)
	// 	return ;
	// left = left_node(p_node->left, fd, sync_fd, data);
	// if (left < 0)
	// 	return ;
	// right = right_node(p_node->right, fd, sync_fd, data);
	// if (right < 0)
	// 	return ;
void	exec_pipe(t_pipe *p_node, t_data *data)
{
	int		fd[2];
	int		sync_fd[2];
	pid_t	left;
	pid_t	right;

	if (create_pipe(fd) == -1 || create_pipe(sync_fd) == -1)
	{
		data->exit_status = 1;
		return ;
	}
	left = left_node(p_node->left, fd, sync_fd, data);
	right = right_node(p_node->right, fd, sync_fd, data);
	signal(SIGINT, SIG_IGN);
	if (left < 0 || right < 0)
	{
		data->exit_status = 1;
		return ;
	}
	close(sync_fd[0]);
	close(sync_fd[1]);
	close(fd[0]);
	close(fd[1]);
	waitpid(left, &data->exit_status, 0);//maybe just the right node exit status is needed? (the overall for this command?)
	waitpid(right, &data->exit_status, 0);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	restore_signal(data->minishell.sa);
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
