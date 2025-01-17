/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:45:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/17 14:33:21 by ewu              ###   ########.fr       */
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

static char	*read_here(char *de, int *exit_status)
{
	char	*content;
	char	*retval;

	content = readline("> ");
	if (!content || !ft_memcmp(content, de, ft_strlen(content) + 1)) 
	{
		if (errno != 0)
			return (print_err("readline", NULL, strerror(errno)), *exit_status = 1, NULL);
		free(content);
		content = NULL;
		*exit_status = 0;
		return (NULL);
	}
	retval = safe_join(content, "\n");
	retval = expand_env(retval, exit_status);
	free(content);
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

void	exec_heredoc(char *de, int *exit_status, t_data *data)
{
	int		fd[2];
	char	*line;

	if (create_pipe(fd, exit_status) < 0)
	{
		print_err("heredoc", de, strerror(errno));
		*exit_status = 1;
	}
	while (1)
	{
		line = read_here(de, exit_status);
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
}
