/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 13:17:08 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 16:21:32 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_err(int fd1, int std_fd)
{
	int	res;

	res = dup2(fd1, std_fd);
	if (res == -1)
	{
		print_err("dup2", NULL, strerror(errno));
		return (-1);
	}
	return (0);
}

int	create_pipe(int *fd, t_data *data)
{
	int	pip;

	pip = pipe(fd);
	if (pip == 0)
	{
		data->exit_status = 0;
		return (0);
	}
	print_err("pipe", NULL, strerror(errno));
	data->exit_status = 1;
	return (-1);
}

pid_t	fork_err(int *fd)
{
	int	id;

	id = fork();
	if (id < 0)
	{
		print_err("fork", NULL, strerror(errno));
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	return (id);
}

//gets exit status from a terminated child process
//child_status must have been set by waitpid() in execve or after pipe
//child_status is reset to 0 in reset_data() after processing
void	update_parent(t_data *data)
{
	if (WIFEXITED(data->child_status))
		data->exit_status = WEXITSTATUS(data->child_status);
	else if (WIFSIGNALED(data->child_status))
	{
		data->exit_status = 128 + WTERMSIG(data->child_status);
		if (WTERMSIG(data->child_status) == SIGINT)
			write(STDERR_FILENO, "\n", 1);
	}
}
