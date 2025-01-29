/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 11:30:10 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 12:03:28 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
//updates the number of arguments of a cmd_node
int	get_cmd_args(t_astnode *cmd_node, t_token *tokens, int arg_tok,
							t_data *data)
{
	char		**argv;
	int			i;

	argv = (char **)gc_malloc((cmd_node->node_type.cmd->arg_nb + 2) * \
														sizeof(char *));
	if (!argv)
		return (set_malloc_error(data), 0);
	argv[0] = cmd_node->token->value;
	i = 1;
	while (tokens[arg_tok].type != TOKEN_EOF && tokens[arg_tok].type != PIPE)
	{
		if (tokens[arg_tok].type == ARGUMENT)
		{
			tokens[arg_tok].value = expand_env(tokens[arg_tok].value, data);
			if (!tokens[arg_tok].value)
				return (set_malloc_error(data), 0);
			if (handle_quotes(&(tokens[arg_tok].value), data) < 0)
				return (0);
			argv[i++] = tokens[arg_tok].value;
		}
		arg_tok++;
	}
	argv[i] = NULL;
	cmd_node->node_type.cmd->argv = argv;
	return (1);
}

//manages a redir node parsing it and setting it to the correct position in the AST with respect to a cmd and other possible redirs of the same cmd
static t_astnode	*update_redir(t_astnode *root, t_token *tok, int *curr_tok, \
									t_data *data)
{
	t_astnode	*last_node;

	if (root->token->type == COMMAND)
		root = parse_redir(tok, curr_tok, root, data);
	else
	{
		last_node = root;
		while (last_node->node_type.redir->right->token->type != COMMAND)
			last_node = last_node->node_type.redir->right;
		last_node->node_type.redir->right = parse_redir(tok, curr_tok, \
									last_node->node_type.redir->right, data);
	}
	return (root);
}

//manages the redirection and words found after a cmd, creating the AST with redirect and args properly added
static t_astnode	*handle_arg_redir(t_astnode *cmd_node, t_token *tok, \
												int *curr_tok, t_data *data)
{
	t_astnode	*root;
	int			arg_tok;

	arg_tok = *curr_tok;
	root = cmd_node;
	while (tok[*curr_tok].type != TOKEN_EOF && tok[*curr_tok].type != PIPE)
	{
		if (tok[*curr_tok].type == WORD)
		{
			tok[*curr_tok].type = ARGUMENT;
			(cmd_node->node_type.cmd->arg_nb)++;
			(*curr_tok)++;
		}
		else if (tok[*curr_tok].type == REDIRECTION)
			root = update_redir(root, tok, curr_tok, data);
	}
	if (!get_cmd_args(cmd_node, tok, arg_tok, data))
		return (NULL);
	return (root);
}

//creates AST nodes for commands
t_astnode	*parse_cmd(t_token *tokens, int *curr_tok, t_data *data)
{
	t_astnode	*cmd_node;

	cmd_node = NULL;
	if (tokens[*curr_tok].type == WORD)
	{
		tokens[*curr_tok].value = expand_env(tokens[*curr_tok].value, data);
		if (!tokens[*curr_tok].value)
			return (set_malloc_error(data), NULL);
		if (handle_quotes(&tokens[*curr_tok].value, data) < 0)
			return (NULL);
		tokens[*curr_tok].type = COMMAND;
		cmd_node = create_cmd_node(&tokens[*curr_tok]);
		if (!cmd_node)
			return (set_malloc_error(data), NULL);
		cmd_node->node_type.cmd->type = get_cmd_type(tokens[*curr_tok].value);
		(*curr_tok)++;
	}
	else if (tokens[*curr_tok].type == REDIRECTION)
		return (parse_redir(tokens, curr_tok, data->ast_root, data));
	else
		return (NULL);
	return (handle_arg_redir(cmd_node, tokens, curr_tok, data));
}
