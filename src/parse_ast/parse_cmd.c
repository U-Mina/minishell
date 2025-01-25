/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:30:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/25 10:03:39 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
//updates the number of arguments of a cmd_node
static char	**get_cmd_args(t_astnode *cmd_node, t_token *tokens, int *curr_tok,
							t_data *data)
{
	char		**argv;
	t_cmd		*cmd;
	int			i;

	cmd_node->node_type.cmd->arg_nb = 0;
	cmd = cmd_node->node_type.cmd;
	while (tokens[*curr_tok + cmd->arg_nb].type == WORD)
		(cmd->arg_nb)++;
	argv = (char **)gc_malloc((cmd->arg_nb + 2) * sizeof(char *));
	// if (!argv)
	// 	return (handle_error(gc_list));
	argv[0] = cmd_node->token->value;
	i = 1;
	while (tokens[*curr_tok].type == WORD)
	{
		//??? should handle the exception that should keep the quotes: when passing shell commands as arguments to another shell interpreter (such as: sh -c "echo hello")!?!?!?!??!?
		tokens[*curr_tok].value = expand_env(tokens[*curr_tok].value, data);
		handle_quotes(&(tokens[*curr_tok].value));
		tokens[*curr_tok].type = ARGUMENT;
		argv[i] = tokens[*curr_tok].value;
		(*curr_tok)++;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}

//disambiguates the tokentype, being a command (binary or builtin)
static t_cmdtype	get_cmd_type(char *cmd)
{
	t_cmdtype		cmd_type;
	char			builtins[7][7];
	int				i;

	ft_strlcpy(builtins[0], "echo", 5);
	ft_strlcpy(builtins[1], "cd", 3);
	ft_strlcpy(builtins[2], "pwd", 4);
	ft_strlcpy(builtins[3], "export", 7);
	ft_strlcpy(builtins[4], "unset", 6);
	ft_strlcpy(builtins[5], "env", 4);
	ft_strlcpy(builtins[6], "exit", 5);
	cmd_type = COMMAND_BINARY;
	i = 0;
	while (i <= 6)
	{
		if (ft_strncmp(cmd, builtins[i], ft_strlen(cmd) + 1) == 0)
		{
			cmd_type = COMMAND_BUILTIN;
			break ;
		}
		else
			i++;
	}
	return (cmd_type);
}

//creates AST nodes for commands
t_astnode	*parse_cmd(t_token *tokens, int *curr_tok, t_data *data)
{
	t_astnode	*cmd_node;

	cmd_node = NULL;
	tokens[*curr_tok].value = expand_env(tokens[*curr_tok].value, data);
	handle_quotes(&tokens[*curr_tok].value);
	if (tokens[*curr_tok].type == WORD)
	{
		tokens[*curr_tok].type = COMMAND;
		cmd_node = create_astnode(&tokens[*curr_tok]);
		// if (!cmd_node)
		// 	return (handle_error(gc_list));
		cmd_node->node_type.cmd->type = get_cmd_type(tokens[*curr_tok].value);
		//check: cmd_node->node_type.cmd->exit_status = data->ex_st??
		(*curr_tok)++;
		cmd_node->node_type.cmd->argv = get_cmd_args(cmd_node, tokens, curr_tok, data);
		if (tokens[*curr_tok].type == REDIRECTION)
			return (parse_redir(tokens, curr_tok, cmd_node, data));
	}
	return (cmd_node);
}
//check: do we need to init the lefe var in t_cmd:
//idea: such as: arg_nv = 0, **env = data->env?? in the init() part??
