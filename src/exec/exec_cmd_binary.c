/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_binary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:31:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/20 13:30:45 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PENDING: Not sure if memory allocation is correctly done here
//Given a command that contains a relative or absolute path to the binary, it isolates and returns the binary name.
static char	*get_binary_name(char *cmd)
{
	char	*cmd_name;
	int		i;
	char	**split;

	split = gc_split(cmd, '/');
	// if (!split)
	// 	handle_error(gc_list);
	i = 0;
	while(split[i + 1])
	{
		gc_free(split[i]);
		i++;
	}
	cmd_name = split[i];
	gc_free(split);
	return (cmd_name);
}

static char	*search_in_path(char *cmd)
{
	char	*paths;
	char	**split_paths;
	char	*full_path;
	int		i;

	paths = getenv("PATH");
	split_paths = gc_split(paths, ':');
	// if (!split_paths)
	// 	handle_error(gc_list);
	i = 0;
	while(split_paths[i])
	{
		full_path = gc_strjoin(gc_strjoin(split_paths[i], "/"), cmd);
		// if (!full_path) //somehow handle when the first ft_strjoin fails
		// 	handle_error(gc_list);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free_double_pointer(split_paths);
			return (full_path);
		}
		gc_free(full_path);
		i++;
	}
	free_double_pointer(split_paths);
	return(NULL);
}

//PENDING: create a path variable (char *) in the ast_node structure, and save it there?

//Checks if an absolute or relative path is given in the input or searches the binary in the PATH environmental variable. 
//Returns an allocated string that represents the path in which to find the binary.
//In the case that the relative or absolute path is given, the token value is changed to that of the cmd name alone.
int	get_path(char *cmd, t_cmd *c_node, t_data *data)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || (cmd[1] == '.' && cmd[2] == '/'))))
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		{
			c_node->path = gc_strdup(cmd);
			cmd = get_binary_name(cmd);
			c_node->argv[0] = cmd;
			return (1);
		}
		else
		{
			print_err("minishell", cmd, "No such file or directory");
			data->exit_status = 1;
			return (0);
		}
	}
	else
	{
		c_node->path = search_in_path(cmd);
		if (!c_node->path)
		{
			print_err("minishell", cmd, "command not found");
			data->exit_status = 1;
			return (0);
		}
		return (1);
	}
}

void	child_proc(t_cmd *cmd, t_data *data)
{
	pid_t	pid;
	char	**env;

	env = data->env;
	if (!env)
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
		execv(cmd->path, cmd->argv);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &data->exit_status, 0);
	init_signal_inter(data->minishell->sa, data->minishell->old_sa);
}
