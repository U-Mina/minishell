/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:30:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/10 12:03:11 by ipuig-pa         ###   ########.fr       */
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
		(*current_token)++;
		command_node->node_type.cmd->argv = get_command_args(command_node, *current_token);
		if (tokens[*current_token].type == REDIRECTION)
			return (parse_redirection(tokens, command_node, current_token, gc_list));
	}
	return (command_node);
}

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
//updates the number of arguments of a command_node
char	**get_command_args(t_astnode *command_node, int *current_token)
{
	char		**argv;
	t_astnode	*arg_node;
	t_cmd		cmd;
	int			i;

	argv[0] = command_node->token->value;
	cmd = command_node->node_type.cmd;
	cmd->args_nbr = 0;
	while (tokens[*current_token + cmd->args_nbr].type == WORD \
			|| tokens[*current_token + cmd->args_nbr].type == QUOTE)
		(cmd->args_nbr)++;
	argv = (char **)gc_malloc((cmd->args_nbr + 2) * sizeof(char *));
	if (!argv)
		return (handle_error(gc_list));
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
t_tokentype	get_command_type(char *command)
{
	t_tokentype	command_type;
	char		**builtins[7];
	int			i;

	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "export";
	builtins[4] = "unset";
	builtins[5] = "env";
	builtins[6] = "exit";
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
