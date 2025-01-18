/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inner_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:08 by ewu               #+#    #+#             */
/*   Updated: 2025/01/18 16:11:00 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//idea: if (ft_strncmp(low_cmd, "./minishell", 12) == 0)
void	to_lower_str(char *str, char *low_cmd);

// bool check_nest_shell(char *arg)
// {
// 	char *lower_cmd;
	
// 	to_lower_str(arg, lower_cmd);
// 	if (ft_strncmp(lower_cmd, "minishell", 10) == 0)
// 		return true;
// 	return false;
// } command_type == minishll

static pid_t fork_err(int *exit_status)
{
	pid_t nest_pid;
	
	nest_pid = fork();
	if (nest_pid == -1)
	{
		*exit_status = 1;
		perror("fork");
		exit(*exit_status);
	}
}

void exec_inner_shell(t_data *data)
{
	pid_t nest_pid;
	char exec_path[12];
	
	exec_path[12] = "./minishell";
	nest_pid = fork_err(data->exit_status);
	if (nest_pid == 0)
	{
		//execve take char *file_path,
		if (execve(exec_path, data->ast_root->node_type.cmd->argv, data->env) < 0)
		{
			data->exit_status = 1;
			perror("execve");
			exit(data->exit_status);
		}
	}
	else if (nest_pid > 0)
		waitpid(nest_pid, data->exit_status, 0);
}
