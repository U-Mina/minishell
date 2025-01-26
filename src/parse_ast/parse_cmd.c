/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:30:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/26 13:31:08 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
//updates the number of arguments of a cmd_node
int	get_cmd_args(t_astnode *cmd_node, t_token *tokens, int arg_tok,
							t_data *data)
{
	char		**argv;
	int			i;

	argv = (char **)gc_malloc((cmd_node->node_type.cmd->arg_nb + 2) * sizeof(char *));
	// if (!argv)
	// 	return (handle_error(gc_list));
	argv[0] = cmd_node->token->value;
	i = 1;
	while (tokens[arg_tok].type != TOKEN_EOF && tokens[arg_tok].type != PIPE)
	{
		if (tokens[arg_tok].type == ARGUMENT)
		{
		//??? should handle the exception that should keep the quotes: when passing shell commands as arguments to another shell interpreter (such as: sh -c "echo hello")!?!?!?!??!?
			tokens[arg_tok].value = expand_env(tokens[arg_tok].value, data);
			if (handle_quotes(&(tokens[arg_tok].value)) < 0)
				return (0);
			argv[i] = tokens[arg_tok].value;
			i++;
		}
		arg_tok++;
	}
	argv[i] = NULL;
	cmd_node->node_type.cmd->argv = argv;
	return (1);
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

static t_astnode	*handle_arg_redir(t_astnode *cmd_node, t_token *tok, \
												int *curr_tok, t_data *data)
{
	t_astnode	*redir_node;
	int			arg_tok;

	arg_tok = *curr_tok;
	redir_node = cmd_node;
	while (tok[*curr_tok].type != TOKEN_EOF && tok[*curr_tok].type != PIPE)
	{
		if (tok[*curr_tok].type == WORD)
		{
			tok[*curr_tok].type = ARGUMENT;
			(cmd_node->node_type.cmd->arg_nb)++;
			(*curr_tok)++;
		}
		else if (tok[*curr_tok].type == REDIRECTION && redir_node == cmd_node)
			redir_node = parse_redir(tok, curr_tok, cmd_node, data);
		else if (tok[*curr_tok].type == REDIRECTION && redir_node != cmd_node)
		{
			redir_node->node_type.redir->right = \
									parse_redir(tok, curr_tok, cmd_node, data);
			redir_node = redir_node->node_type.redir->right;
		}
	}
	if (!get_cmd_args(cmd_node, tok, arg_tok, data))
		return (NULL);
	return (redir_node);
}


//creates AST nodes for commands
t_astnode	*parse_cmd(t_token *tokens, int *curr_tok, t_data *data)
{
	t_astnode	*cmd_node;

	cmd_node = NULL;
	if (tokens[*curr_tok].type == WORD)
	{
		tokens[*curr_tok].value = expand_env(tokens[*curr_tok].value, data);
		if (handle_quotes(&tokens[*curr_tok].value) < 0)
			return (NULL);
		tokens[*curr_tok].type = COMMAND;
		cmd_node = create_astnode(&tokens[*curr_tok]);
		// if (!cmd_node)
		// 	return (handle_error(gc_list));
		cmd_node->node_type.cmd->type = get_cmd_type(tokens[*curr_tok].value);
		(*curr_tok)++;
	}
	else if (tokens[*curr_tok].type == REDIRECTION)
		return (parse_redir(tokens, curr_tok, data->ast_root, data));
	return (handle_arg_redir(cmd_node, tokens, curr_tok, data));
}
//check: do we need to init the lefe var in t_cmd:
//idea: such as: arg_nv = 0, **env = data->env?? in the init() part??
