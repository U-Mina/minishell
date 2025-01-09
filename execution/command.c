/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/09 12:44:36 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_command_args(t_astnode *command_node)
{
	char		**args;
	t_astnode	*arg_node;
	int			i;

	args = (char **)gc_malloc((command_node->args_nbr) * sizeof(char *));
	arg_node = command_node->next_arg;
	args[0] = command_node->token->value;
	i = 1;
	while (arg_node)
	{
		args[i] = arg_node->token->value;
		arg_node = arg_node->next_arg;
		i++;
	}
	args[i] = NULL;
	return (args);
}
