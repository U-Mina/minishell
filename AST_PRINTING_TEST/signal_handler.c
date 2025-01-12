/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/11 17:35:31 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/12 16:32:48 by ipuig-pa         ###   ########.fr       */
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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

//call it in the child process, before execve??? 
//Be sure that signal is enough, and in the other case sigaction is needed (at least to store previous state, but for what else it is interesting?? mask??? need to do it???)
//Be sure that SIG_DFL will work in any system

//handles SIGINT and SIGQUIT in shell execution mode
void	init_signal_exec(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

//restores the signals actions to those in the original state
void	restore_signal(struct sigaction *old_sa)
{
	sigaction(SIGINT, &old_sa[0], NULL);
	sigaction(SIGQUIT, &old_sa[1], NULL);
}
