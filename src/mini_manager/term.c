/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 11:18:06 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 15:25:02 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//exits cleanly when Ctrl+D is pressed in the prompt
void	exit_eof(t_minishell *minishell)
{
	printf("exit\n");
	term_minishell(minishell, 1);
}

//restores the termios attributes and the signal actions to the original, and
//cleans all allocated items (gc_list) before exiting shell
void	term_minishell(t_minishell	*minishell, int exit_status)
{
	int	rv;

	rv = exit_status;
	rl_clear_history();
	restore_signal(minishell->old_sa);
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->old_term));
	gc_clean();
	exit (rv);
}
