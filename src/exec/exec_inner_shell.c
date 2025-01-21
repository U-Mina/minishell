/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_inner_shell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:50:08 by ewu               #+#    #+#             */
/*   Updated: 2025/01/21 10:55:47 by ewu              ###   ########.fr       */
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

static pid_t	fork_err(int *exit_status)
{
	pid_t	nest_pid;

	nest_pid = fork();
	if (nest_pid == -1)
	{
		*exit_status = 1;
		perror("fork");
		exit(*exit_status);
	}
	return (nest_pid);
}

void	exec_inner_shell(t_data *data)
{
	pid_t	nest_pid;
	char	exec_path[12];

	//check that no arguments are passed, and see if it should work with pipes, etc (reproduce bash behavior)
	ft_strlcpy(exec_path, "./minishell", 12);
	nest_pid = fork_err(&data->exit_status);
	if (nest_pid == 0)
	{
		//execve take char *file_path,
		execve(exec_path, data->ast_root->node_type.cmd->argv, data->env);
		// if (execve(exec_path, data->ast_root->node_type.cmd->argv, data->env) < 0)
		// {
		// 	data->exit_status = 1;
		// 	perror("execve");
		// 	// exit(data->exit_status);
		// }
	}
	// else if (nest_pid > 0)
	//check: error check not implemented now, may add exeve()<0 check later
	waitpid(nest_pid, &data->exit_status, 0);
	if (WIFEXITED(data->exit_status))
		data->exit_status = WEXITSTATUS(data->exit_status);
}
