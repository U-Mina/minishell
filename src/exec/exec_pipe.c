/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 14:03:59 by ewu               #+#    #+#             */
/*   Updated: 2025/01/29 13:19:51 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * - create pipe
 * - redirct and connect pipe
 * - close and clean
 */
static int	left_node(t_astnode *ast_node, int *fd, int *sync_fd, t_data *data)
{
	pid_t	left;

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
		exit(data->exit_status);
	}
	return (left);
}

static int	wait_left_redir(int sync_fd)
{
	char	buffer[7];
	size_t	bytes_read;

	bytes_read = read(sync_fd, buffer, 7);
	if (bytes_read == 6 && ft_strncmp(buffer, "sigint", 6) == 0)
		g_signal = SIGINT;
	else if (bytes_read != 4 || ft_strncmp(buffer, "done", 4) != 0)
	{
		perror("Pipe synchronization failed");
		return (0);
	}
	return (1);
}

static int	right_node(t_astnode *ast_node, int *fd, int *sync_fd, t_data *data)
{
	pid_t	right;

	right = fork_err(fd);
	if (right == -1)
		return (data->exit_status = 1, -1);
	if (right == 0)
	{
		signal(SIGINT, SIG_IGN);
		close(sync_fd[1]);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		if (!wait_left_redir(sync_fd[0]))
			exit (1);
		close(sync_fd[0]);
		restore_signal(data->minishell.sa);
		if (g_signal != SIGINT)
		{
			exec_ast(ast_node, data);
			exit(data->exit_status);
		}
		exit(1);
	}
	return (right);
}

void	exec_pipe(t_pipe *p_node, t_data *data)
{
	int		fd[2];
	int		sync_fd[2];
	pid_t	left;
	pid_t	right;

	if (create_pipe(fd, data) == -1 || create_pipe(sync_fd, data) == -1)
		return ;
	left = left_node(p_node->left, fd, sync_fd, data);
	right = right_node(p_node->right, fd, sync_fd, data);
	signal(SIGINT, SIG_IGN);
	if (left < 0 || right < 0)
		return ;
	close(sync_fd[0]);
	close(sync_fd[1]);
	close(fd[0]);
	close(fd[1]);
	waitpid(left, NULL, 0);
	waitpid(right, &data->exit_status, 0);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	restore_signal(data->minishell.sa);
}
