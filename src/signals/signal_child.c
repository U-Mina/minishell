/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:18:44 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 16:20:15 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//handles SIGINT and SIGQUIT in shell execution mode
void	init_exec_mode(void)
{
	struct termios		exec_term;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	tcgetattr(STDIN_FILENO, &exec_term);
	exec_term.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &exec_term);
}

//handles SIGQUIT action if it was pressed on the last child node
void	handle_child_sigquit(t_data *data)
{
	if (data->child_status == 0)
		return ;
	if (WIFSIGNALED(data->child_status))
	{
		if (WTERMSIG(data->child_status) == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
	}
}
