/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:30:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/15 12:45:27 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//creates AST nodes for commands
t_astnode	*parse_command(t_token *tokens, int *current_token)
{
	t_astnode	*command_node;

	command_node = NULL;
	if (tokens[*current_token].type == QUOTE)
		del_cmd_quotes(tokens, current_token);
	if (tokens[*current_token].type == WORD)
	{
		tokens[*current_token].type = COMMAND;
		command_node = create_astnode(&tokens[*current_token]);
		// if (!command_node)
		// 	return (handle_error(gc_list));
		command_node->node_type.cmd->type = get_command_type(tokens[*current_token].value);
		command_node->node_type.cmd->exit_status = 0;
		(*current_token)++;
		command_node->node_type.cmd->argv = get_command_args(command_node, tokens, current_token);
		if (tokens[*current_token].type == REDIRECTION)
			return (parse_redirection(tokens, current_token, command_node));
	}
	// else
	// {
	// 	// //handle error correclty!!!! here or during execution!!?!?
	// 	// printf("%s: Command not found\n");//correctly named and finish AST_node construction
	// 	// exit_status (127);
	// }
	return (command_node);
}

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
//updates the number of arguments of a command_node
char	**get_command_args(t_astnode *command_node, t_token *tokens, int *current_token)
{
	char		**argv;
	t_cmd		*cmd;
	int			i;

	command_node->node_type.cmd->arg_nb = 0;
	cmd = command_node->node_type.cmd;
	while (tokens[*current_token + cmd->arg_nb].type == WORD \
			|| tokens[*current_token + cmd->arg_nb].type == QUOTE)
		(cmd->arg_nb)++;
	argv = (char **)gc_malloc((cmd->arg_nb + 2) * sizeof(char *));
	// if (!argv)
	// 	return (handle_error(gc_list));
	argv[0] = command_node->token->value;
	i = 1;
	while (tokens[*current_token].type == WORD \
			|| tokens[*current_token].type == QUOTE)
	{
		tokens[*current_token].type = ARGUMENT;
		argv[i] = tokens[*current_token].value;
		(*current_token)++;
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
	while (i <= 6)
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

//removes the quotes of the the token value and converts it to a WORD token, so it can be processed as a command
void	del_cmd_quotes(t_token *tokens, int *current_token)
{
	char	*trimmed;
	char	quote[2];

	quote[0] = tokens[*current_token].value[0];
	quote[1] = '\0';
	trimmed = gc_strtrim(tokens[*current_token].value, quote);
	gc_free(tokens[*current_token].value);
	tokens[*current_token].value = trimmed;
	tokens[*current_token].type = WORD;
}
