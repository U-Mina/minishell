/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:35:31 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/30 11:55:38 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//initiates the signals that should be handled during shell interactive mode
void	init_signal_inter(struct sigaction *sa, struct sigaction *old_sa)
{
	sigemptyset(&(sa[0].sa_mask));
	sa[0].sa_handler = &signal_handler;
	sa[0].sa_flags = 0;
	sigemptyset(&(sa[1].sa_mask));
	sa[1].sa_handler = SIG_IGN;
	sa[1].sa_flags = 0;
	sigaction(SIGINT, &sa[0], &old_sa[0]);
	sigaction(SIGQUIT, &sa[1], &old_sa[1]);
}

//handles SIGINT action in interactive mode
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		if (g_signal != SIGINT_H && g_signal != SIGEOF)
			write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (g_signal != SIGINT_H && g_signal != SIGEOF)
			g_signal = SIGINT_I;
	}
}

//handles SIGINT action in heredoc mode
void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT_H;
		write(STDERR_FILENO, "\n", 1);
		close(STDIN_FILENO);
	}
}

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

//restores the signals actions to those in the original state
void	restore_signal(struct sigaction *old_sa)
{
	sigaction(SIGINT, &old_sa[0], NULL);
	sigaction(SIGQUIT, &old_sa[1], NULL);
}
