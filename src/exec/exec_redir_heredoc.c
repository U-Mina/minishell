/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:45:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/28 19:47:58 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo: in heredoc, $home etc case need to be handlesd!!!

// static int	heredoc(t_redir *redir, int fd, int *exit_status)
// {
// 	if (fd != 0)
// 		close(fd);
// 	fd = redir->heredoc_fd;
// 	if (fd != -1)
// 	{
// 		*exit_status = 0;
// 		return (fd);
// 	}
// 	print_err("heredoc", redir->left, strerror(errno));
// 	*exit_status = 1;
// 	return (-1);
// }

static void	init_heredoc(struct sigaction *h_sa, t_data *data)
{
	data->fd[0] = dup(STDIN_FILENO);
	data->fd[1] = dup(STDOUT_FILENO);
	dup2(data->o_fd[0], STDIN_FILENO);
	dup2(data->o_fd[1], STDOUT_FILENO);
	sigemptyset(&(h_sa[0].sa_mask));
	h_sa[0].sa_handler = &heredoc_signal_handler;
	h_sa[0].sa_flags = 0;
	sigemptyset(&(h_sa[1].sa_mask));
	h_sa[1].sa_handler = SIG_IGN;
	h_sa[1].sa_flags = 0;
	sigaction(SIGINT, &h_sa[0], NULL);
	sigaction(SIGQUIT, &h_sa[1], NULL);
}

static void	term_heredoc(t_data *data)
{
	dup2(data->fd[0], STDIN_FILENO);
	dup2(data->fd[1], STDOUT_FILENO);
	sigaction(SIGINT, &data->minishell.sa[0], NULL);
	sigaction(SIGQUIT, &data->minishell.sa[1], NULL);
}

static char	*read_here(char *de, int *exit_status, t_data *data, bool quote)
{
	char				*content;
	char				*retval;
	struct sigaction	h_sa[2];

	init_heredoc(h_sa, data);
	content = readline("> ");
	if (!content || !ft_memcmp(content, de, ft_strlen(content) + 1) || *content < 0) //check properly the behavior when Ctrl-D is pressed (*content < 0) if we should set error different, exit status???
	{
		if (errno != 0 && g_signal != SIGINT)
			return (print_err("readline", NULL, strerror(errno)), *exit_status = 1, NULL);
		free(content);
		content = NULL;
		*exit_status = 0;
		term_heredoc(data);
		rl_on_new_line();
		return (NULL);
	}
	retval = gc_strjoin(content, "\n");
	if (!quote)
		retval = expand_env(retval, data);
	free(content);
	term_heredoc(data);
	return (retval);
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

	if (create_pipe(fd) < 0)
	{
		print_err("heredoc", de, strerror(errno));
		*exit_status = 1;
	}
	while (1)
	{
		line = read_here(de, exit_status, data, quote);
		if (line == NULL)//finished reading(EOF) or meet delim
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
	if (g_signal == SIGINT)
	{
		data->heredoc_fd = -1;
		data->exit_status = 1;
	}
}
