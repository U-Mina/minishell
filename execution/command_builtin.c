/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 12:35:12 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec_builtins(t_astnode *cmd_node)
{
	char **args;

	args = cmd_node->node_type.cmd->argv;
	if (ft_strncmp(ft_tolower(args[0]), "echo", 5) == 0)
		return (ft_echo(args, cmd_node->node_type.cmd->exit_status), 0);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (ft_cd(args, &cmd_node->node_type.cmd->env, cmd_node->node_type.cmd->exit_status), 0);
	else if (ft_strncmp(ft_tolower(args[0]), "pwd", 4) == 0)
		return (ft_pwd(cmd_node->node_type.cmd->exit_status), 0);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (ft_export(&cmd_node->node_type.cmd->env, args, cmd_node->node_type.cmd->exit_status), 0);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (ft_unset(args, &cmd_node->node_type.cmd->env, cmd_node->node_type.cmd->exit_status), 0);
	else if (ft_strncmp(ft_tolower(args[0]), "env", 4) == 0)
		return (ft_env(cmd_node->node_type.cmd->env, cmd_node->node_type.cmd->exit_status), 0);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_exit(args, cmd_node->node_type.cmd->exit_status), 0);
	return -2;//set -2 for error check
}
//args = get_command_args(cmd_node) -->already done in parsing
//exit_status is inited in struct, so pass the value

//todo: 
exec_cmd();
builtin_case_match();
binary_path_find();
exec_child();
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
