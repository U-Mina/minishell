/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 11:29:35 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo: 
exec_cmd();
builtin_case_match();
binary_path_find();
exec_child();

/** *t_tokentype	get_command_type(char *command, char **builtins)
{
	t_tokentype	command_type;
	int			i;

	command_type = COMMAND_BINARY;
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(command, builtins[i], ft_strlen(command)) == 0)
		{
			command_type = COMMAND_BUILTIN;
			break ;
		}
		else
			i++;
	}
	return (command_type);
}
 */
int exec_command(t_astnode *astnode, int *exit_status)
{
	t_tokentype *type;

	if (type == COMMAND_BINARY)
		return (exec_binary());
	else if (type == COMMAND_BUILTIN)
		return (exec_builtins(astnode));
	else
	{
		print_err("minishell", astnode->token->value, "command not found");
		*exit_status = 1;
		return -1;
	}
}

/**
 * case sensitive: unset, export, cd, exit
 * not-sensitive: pwd/PWD, env/ENV, echo/ECHO
 */
//check: is clean function need to be called after each direct
//todo: to connect and pass *exit_status;
int exec_builtins(t_astnode *cmd_node, int *exit_status)
{
	char **args;

	args = get_command_args(cmd_node);
	exit_status = cmd_node->exit_status; //not sure, may change
	if (ft_strncmp(ft_tolower(args[0]), "echo", 5) == 0)
		return (ft_echo(args, cmd_node->exit_status), 0);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (ft_cd(args, &cmd_node->env, cmd_node->exit_status), 0);
	else if (ft_strncmp(ft_tolower(args[0]), "pwd", 4) == 0)
		return (ft_pwd(cmd_node->exit_status), 0);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (ft_export(&cmd_node->env, args, cmd_node->exit_status), 0);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (ft_unset(args, &cmd_node->env, cmd_node->exit_status), 0);
	else if (ft_strncmp(ft_tolower(args[0]), "env", 4) == 0)
		return (ft_env(cmd_node->env, cmd_node->exit_status), 0);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_exit(args, cmd_node->exit_status), 0);
	return -2;//set -2 for error check
}
