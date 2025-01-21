/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 17:38:11 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/21 12:43:09 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cmd(t_astnode *cmd_node, t_data *data)
{
	t_cmd	*cmd;

	cmd = cmd_node->node_type.cmd;
	if (cmd->argv && cmd->argv[0] == NULL)
	{
		gc_free(cmd->argv);
		cmd->argv = NULL;
	}
	if (cmd->argv && cmd->argv[0])
	{
		if (cmd->type == COMMAND_BUILTIN)
			exec_builtins(cmd, data);
		else if (cmd->type == COMMAND_BINARY)
		{
			if (get_path(cmd_node->token->value, cmd_node->node_type.cmd, data))
				child_proc(cmd, data);
		}
	}
}
