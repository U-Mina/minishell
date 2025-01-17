/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:45:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/16 19:00:01 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo: in heredoc, $home etc case need to be handlesd!!!

//changed to non-static
// static int create_pip(int fd[2], int *exit_status)
// {
// 	int pip;
// 	pip = pipe(fd);
// 	if (pip == 0)
// 	{
// 		*exit_status = 0;
// 		return 0;
// 	}
// 	print_err("pipe", NULL, strerror(errno));
// 	*exit_status = 1;
// 	return -1;
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
	//here to add '$' sign handler(after comparing with the de, which has to be literal). If no matching env var is found, just a new line is taken
	retval = safe_join(content, "\n");
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
