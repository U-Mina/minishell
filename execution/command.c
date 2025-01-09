/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/09 14:49:51 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo: 
exec_cmd();
builtin_case_match();
binary_path_find();
exec_child();

//returns an array of strings, the first one of which is the command/program name and each of the following ones are the flags/parameters for the command
char	**get_command_args(t_astnode *command_node)
{
	char		**argv;
	t_astnode	*arg_node;
	int			i;

	argv = (char **)gc_malloc((command_node->args_nbr + 2) * sizeof(char *));
	arg_node = command_node->next_arg;
	argv[0] = command_node->token->value;
	i = 1;
	while (arg_node)
	{
		argv[i] = arg_node->token->value;
		arg_node = arg_node->next_arg;
		i++;
	}
	argv[i] = NULL;
	return (argv);
}
