/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:45:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 12:02:52 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_heredoc(struct sigaction *h_sa, t_data *data)
{
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	if (dup_err(data->o_fd[0], STDIN_FILENO) == -1)
	{
		data->exit_status = 1;
		return (0);
	}
	if (dup_err(data->o_fd[1], STDOUT_FILENO) == -1)
	{
		data->exit_status = 1;
		return (0);
	}
	sigemptyset(&(h_sa[0].sa_mask));
	h_sa[0].sa_handler = &heredoc_signal_handler;
	h_sa[0].sa_flags = 0;
	sigemptyset(&(h_sa[1].sa_mask));
	h_sa[1].sa_handler = SIG_IGN;
	h_sa[1].sa_flags = 0;
	sigaction(SIGINT, &h_sa[0], NULL);
	sigaction(SIGQUIT, &h_sa[1], NULL);
	return (1);
}

static void	term_heredoc(t_data *data)
{
	sigaction(SIGINT, &data->minishell.sa[0], NULL);
	sigaction(SIGQUIT, &data->minishell.sa[1], NULL);
	if (dup_err(data->fd[0], STDIN_FILENO) == -1)
		data->exit_status = 1;
	if (dup_err(data->fd[1], STDOUT_FILENO) == -1)
		data->exit_status = 1;
}

static char	*read_here(char *de, int *exit_status, t_data *data,
						bool quote)
{
	char				*content;
	char				*retval;
	struct sigaction	h_sa[2];

	if (!init_heredoc(h_sa, data))
		return (term_heredoc(data), NULL);
	content = readline("> ");
	if (!content && g_signal != SIGINT_H)
		g_signal = SIGEOF;
	if (!content || !ft_memcmp(content, de, ft_strlen(content) + 1))
	{
		if (errno != 0 && g_signal != SIGINT_H)
		{
			print_err("readline", NULL, strerror(errno));
			return (*exit_status = 1, NULL);
		}
		free(content);
		*exit_status = 0;
		return (term_heredoc(data), NULL);
	}
	retval = gc_strjoin(content, "\n");
	if (!quote)
		retval = expand_env(retval, data);
	free(content);
	return (term_heredoc(data), retval);
}

static int	write_pipe(int *fd, char *retval, int *exit_status)
{
	if (write(fd[1], retval, ft_strlen(retval)) == -1)
	{
		gc_free(retval);
		print_err("write", NULL, strerror(errno));
		*exit_status = 1;
		return (-1);
	}
	*exit_status = 0;
	gc_free(retval);
	return (0);
}

void	exec_heredoc(char *de, int *exit_status, t_data *data, bool quote)
{
	int		fd[2];
	char	*line;

	if (create_pipe(fd, data) < 0)
		return (print_err("heredoc", de, strerror(errno)));
	while (1)
	{
		line = read_here(de, exit_status, data, quote);
		if (!line)
			break ;
		if (write_pipe(fd, line, exit_status) < 0)
		{
			gc_free(line);
			print_err("heredoc", de, strerror(errno));
			*exit_status = 1;
			close(fd[0]);
			close(fd[1]);
			return ;
		}
	}
	close(fd[1]);
	data->heredoc_fd = fd[0];
	data->fd[0] = fd[0];
}
