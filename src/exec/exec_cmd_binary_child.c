/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_binary_child.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:31:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 12:57:02 by ipuig-pa         ###   ########.fr       */
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
		init_exec_mode();
		execve(cmd->path, cmd->argv, data->env);
		perror("execve");
		exit(1);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &data->child_status, 0);
	restore_signal(data->minishell.sa);
	tcsetattr(STDIN_FILENO, TCSANOW, &(data->minishell.term));
}
