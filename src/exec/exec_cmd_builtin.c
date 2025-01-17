/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/17 13:14:32 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	to_lower_str(char *str, char *low_cmd)
{
	int	i;

	i = 0;
	while(str[i] != '\0' && i <= 7)
	{
		low_cmd[i] = ft_tolower(str[i]);
		i++;
	}
	low_cmd[i] = '\0';
}

int	exec_builtins(t_cmd *cmd, t_data *data)
{
	char	**args;
	char	low_cmd[7];

	args = cmd->argv;
	to_lower_str(args[0], low_cmd);
	if (ft_strncmp(low_cmd, "echo", 5) == 0)
		return (ft_echo(args, data->exit_status), 0);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (ft_cd(args, &cmd->env, data->exit_status), 0);
	else if (ft_strncmp(low_cmd, "pwd", 4) == 0)
		return (ft_pwd(data->exit_status), 0);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (ft_export(&cmd->env, args, data->exit_status), 0);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (ft_unset(args, &cmd->env, data->exit_status), 0);
	else if (ft_strncmp(low_cmd, "env", 4) == 0)
		return (ft_env(cmd->env, data->exit_status), 0);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_exit(args, data->exit_status), 0);
	return -2;//set -2 for error check
}
//args = get_command_args(cmd_node) -->already done in parsing
//exit_status is inited in struct, so pass the value

//todo: 
// exec_cmd();
// builtin_case_match();
// binary_path_find();
// exec_child();
/**
 * case sensitive: unset, export, cd, exit
 * not-sensitive: pwd/PWD, env/ENV, echo/ECHO
 */
//check: is clean function need to be called after each direct
//todo: to connect and pass *exit_status;

// int exec_command(t_astnode *astnode, int *exit_status)
// {
// 	t_tokentype *type;

// 	if (type == COMMAND_BINARY)
// 		return (exec_binary());
// 	else if (type == COMMAND_BUILTIN)
// 		return (exec_builtins(astnode));
// }
