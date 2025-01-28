/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:54:34 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/28 19:55:00 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check: try bad input
//debug: not sure what para to pass
void	init_cmd_node(t_cmd *cmd_node)
{
	cmd_node->arg_nb = 0;
	cmd_node->argv = NULL;
	cmd_node->path = NULL;
}

void	init_redir_node(t_redir *redir_node)
{
	redir_node->left = NULL;
	redir_node->right = NULL;
}

void	init_pipe_node(t_pipe *pipe_node)
{
	pipe_node->left = NULL;
	pipe_node->right = NULL;
}
