/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_binary.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 17:31:50 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 11:55:24 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//PENDING: create a path variable (char *) in the ast_node structure, and save it there?

// typedef struct s_astnode
// {
// 	int					fd[2];
// 	t_token				*token;
// 	t_pipe				*pipe;
// 	t_redir				*redirect;
// 	t_cmd				*cmd;
// }						t_astnode;

// typedef struct s_redir
// {
// 	int					fd;
// 	t_token				*token;
// 	t_redir			*right;
// 	t_redir			*left;

// }						t_redir;

// typedef struct s_cmd
// {
// 	int		args_nbr;
// 	char	**argv;
// 	char	*path;
// 	char	**env; //or wherever it is
// }			t_cmd;

//Checks if an absolute or relative path is given in the input or searches the binary in the PATH environmental variable. 
//Returns an allocated string that represents the path in which to find the binary.
//In the case that the relative or absolute path is given, the token value is changed to that of the cmd name alone.
void	get_path(t_astnode *ast_node, int *exit_status)
{
	char	*cmd;

	cmd = ast_node->token->value;
	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || (cmd[1] == '.' && cmd[2] == '/'))))
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
		{
			ast_node->cmd->path = ft_strdup(cmd); //need to allocate somehow, change strdup or gc_malloc somehow???
			ast_node->token->value = get_binary_name(cmd, '/');
			ast_node->node_type.cmd->argv[0] = ast_node->token->value;
		}
		else
		{
			print_err("minishell: ", cmd, ": No such file or directory");
			*exit_status = 1;
		}
	}
	else
	{
		ast_node->cmd->path = search_in_path(cmd);
		if (!ast_node->cmd->path)
		{
			print_err("minishell: ", cmd, ": command not found");
			*exit_status = 1;
		}
	}
}

//PENDING: Not sure if memory allocation is correctly done here
//Given a command that contains a relative or absolute path to the binary, it isolates and returns the binary name.
char	*get_binary_name(char *cmd)
{
	char	*cmd_name;
	int		i;

	split = ft_split(cmd, '/');
	// if (!split)
	// 	handle_error(gc_list);
	while(split[i + 1])
	{
		free(split[i]);
		i++;
	}
	cmd_name = split[i];
	free(split);
	return (cmd_name);
}

char	*search_in_path(char *cmd)
{
	char	*paths;
	char	**split_paths;
	char	*full_path;
	int		i;

	paths = //somehow get env variable PATH
	split_paths = ft_split(path, ':');
	// if (!split_paths)
	// 	handle_error(gc_list);
	while(split_paths[i])
	{
		full_path = ft_strjoin(ft_strjoin(split_paths[i], "/"), cmd);
		// if (!full_path) //somehow handle when the first ft_strjoin fails
		// 	handle_error(gc_list);
		if (access(full_path, F_OK) == 0 && access(full_path, X_OK) == 0)
		{
			free_double_pointer(split_paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_double_pointer(split_paths);
	return(NULL);
}
