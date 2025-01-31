/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_binary_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:05:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/31 17:33:10 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Given a command that contains a relative or absolute path to the binary, 
//it isolates and returns the binary name.
static char	*get_binary_name(char *cmd, t_data *data)
{
	char	*cmd_name;
	int		i;
	char	**split;

	split = gc_split(cmd, '/');
	if (!split)
		return (set_malloc_error(data), NULL);
	i = 0;
	while (split[i + 1])
	{
		gc_free(split[i]);
		i++;
	}
	cmd_name = split[i];
	gc_free(split);
	return (cmd_name);
}

//searches the cmd name of a binary in the current working directory and, 
//if found and executable, returns the full path
static char	*search_inner(char *cmd, t_data *data)
{
	char	*paths;
	char	*full_path;

	paths = env_var_value(data->env, "PWD");
	if (!paths)
		return (NULL);
	full_path = gc_strjoin(gc_strjoin(paths, "/"), cmd);
	if (!full_path)
		return (set_malloc_error(data), NULL);
	if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		return (full_path);
	gc_free(full_path);
	return (NULL);
}

//searches the cmd name of a binary in the paths included in "PATH", 
//if found and executable, returns the full path
static char	*search_in_path(char *cmd, t_data *data)
{
	char	*paths;
	char	**split_paths;
	char	*full_path;
	int		i;

	paths = env_var_value(data->env, "PATH");
	if (!paths)
		return (NULL);
	split_paths = gc_split(paths, ':');
	if (!split_paths)
		return (set_malloc_error(data), NULL);
	i = 0;
	while (split_paths[i])
	{
		full_path = gc_strjoin(gc_strjoin(split_paths[i], "/"), cmd);
		if (!full_path)
			return (set_malloc_error(data), NULL);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
			break ;
		gc_free(full_path);
		full_path = NULL;
		i++;
	}
	free_double_pointer(split_paths);
	return (full_path);
}

//PART OF GET_PATH
//when the arg is a path itself, it copies this path to the c_node->path. 
//The token value is changed to that of the cmd name alone.
//If it is not an execultable path, it fails, and prints error.
static int	copy_path(char *cmd, t_cmd *c_node, t_data *data)
{
	struct stat	path_stat;

	if (check_permission(cmd, data) && stat(cmd, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
		{
			c_node->path = gc_strdup(cmd);
			if (!c_node->path)
				return (set_malloc_error(data), 0);
			cmd = get_binary_name(cmd, data);
			if (!cmd)
				return (set_malloc_error(data), 0);
			return (c_node->argv[0] = cmd, 1);
		}
		else if (S_ISDIR(path_stat.st_mode))
		{
			print_err("minishell", cmd, "is a directory");
			return (data->exit_status = 126, 0);
		}
	}
	return (0);
}

//Checks if a path is given or searches the binary in the PATH env.
//Returns allocated string of the path in which to find the binary.
int	get_path(char *cmd, t_cmd *c_node, t_data *data)
{
	if (!cmd || (*cmd == '\0' && !c_node->quote))
		return (0);
	else if (*cmd == '\0' && c_node->quote)
	{
		print_err("minishell", cmd, "command not found");
		data->exit_status = 127;
		return (0);
	}
	if (ft_strrchr(cmd, '/'))
		return (copy_path(cmd, c_node, data));
	else
	{
		c_node->path = search_in_path(cmd, data);
		if (!c_node->path)
			c_node->path = search_inner(cmd, data);
		if (!c_node->path)
		{
			print_err("minishell", cmd, "command not found");
			data->exit_status = 127;
			return (0);
		}
		return (1);
	}
}
