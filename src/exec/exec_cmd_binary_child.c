/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_binary_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:31:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 15:37:19 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//forks the process to execve for a binnary found in cmd->path
void	child_proc(t_cmd *cmd, t_data *data)
{
	pid_t	pid;

	if (!data->env)
		return ;
	pid = fork ();
	if (pid == -1)
	{
		print_err("fork", NULL, strerror(errno));
		data->exit_status = 1;
		return ;
	}
	if (pid == 0)
	{
		init_signal_exec();
		execve(cmd->path, cmd->argv, data->env);
		perror("execve");
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &data->exit_status, 0);
	restore_signal(data->minishell.sa);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
	else if (WIFSIGNALED(data->exit_status))
		data->exit_status = 128 + WTERMSIG(data->exit_status);
}
