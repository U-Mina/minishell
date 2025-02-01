/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:35:31 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/02/01 12:43:21 by ipuig-pa         ###   ########.fr       */
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
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = SIGINT;
	}
}

//handles SIGINT action in heredoc mode
void	heredoc_signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = SIGINT;
		printf("\033[A\033[K> ");
		rl_done = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
	}
}

//restores the signals actions to those in the original state
void	restore_signal(struct sigaction *old_sa)
{
	sigaction(SIGINT, &old_sa[0], NULL);
	sigaction(SIGQUIT, &old_sa[1], NULL);
}
