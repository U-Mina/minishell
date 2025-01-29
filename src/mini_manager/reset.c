/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 10:04:25 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 11:11:22 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to reset data structure between readline calls 
void	reset_data(t_data *data)
{
	data->heredoc_fd = -1;
	dup2(data->o_fd[0], STDIN_FILENO);
	data->fd[0] = STDIN_FILENO;
	dup2(data->o_fd[1], STDOUT_FILENO);
	data->fd[1] = STDOUT_FILENO;
	if (data->ast_root)
		free_ast(data->ast_root);
	if (data->tokens)
		gc_free(data->tokens);
	data->malloc_err = false;
}

//updates the exit status depending on the status of the global variable g_signal (if SIGINT has been received) and restores to 0
void	reset_signal(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->exit_status = 1;
		g_signal = 0;
	}
}
