/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:30:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 17:37:44 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates AST nodes for commands
t_astnode	*parse_command(t_token *tokens, int *current_token, t_gc_list *gc_list)
{
	t_astnode	*command_node;

	command_node = NULL;
	if (tokens[*current_token].type == WORD)
	{
		tokens[*current_token].type = COMMAND;
		command_node = create_astnode(&tokens[*current_token], gc_list);
		if (!command_node)
			return (handle_error(gc_list));
		command_node->node_type.cmd->type = get_command_type(tokens[*current_token].value);
		command_node->node_type.cmd->exit_status = 0;
		command_node->node_type.cmd->argv = get_command_args(command_node, tokens, current_token, gc_list);
		(*current_token)++;
		if (tokens[*current_token].type == REDIRECTION)
			return (parse_redirection(tokens, current_token, command_node, gc_list));
	}
	return (command_node);
}

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
//updates the number of arguments of a command_node
char	**get_command_args(t_astnode *command_node, t_token *tokens, int *current_token, t_gc_list *gc_list)
{
	char		**argv;
	t_cmd		*cmd;
	int			i;

	cmd = command_node->node_type.cmd;
	cmd->args_nbr = 0;
	while (tokens[*current_token + cmd->args_nbr].type == WORD \
			|| tokens[*current_token + cmd->args_nbr].type == QUOTE)
		(cmd->args_nbr)++;
	argv = (char **)gc_malloc((cmd->args_nbr + 2) * sizeof(char *), gc_list);
	if (!argv)
		return (handle_error(gc_list));
	argv[0] = command_node->token->value;
	i = 1;
	while (tokens[*current_token].type == WORD \
			|| tokens[*current_token].type == QUOTE)
	{
		tokens[*current_token].type = ARGUMENT;
		argv[i] = tokens[*current_token].value;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

//disambiguates the tokentype, being a command (binary or builtin)
t_cmdtype	get_command_type(char *command)
{
	t_cmdtype		command_type;
	char			builtins[7][7];
	int				i;

	ft_strlcpy(builtins[0], "echo", 7);
	ft_strlcpy(builtins[1], "cd", 7);
	ft_strlcpy(builtins[2], "pwd", 7);
	ft_strlcpy(builtins[3], "export", 7);
	ft_strlcpy(builtins[4], "unset", 7);
	ft_strlcpy(builtins[5], "env", 7);
	ft_strlcpy(builtins[6], "exit", 7);
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


