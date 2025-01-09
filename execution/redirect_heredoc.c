/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:45:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/09 15:19:32 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int read_here(char *de, char **content, int *exit_status)
{
	*content = readline("> ");
	if (!*content) 
	{
		if (errno != 0)
			return (print_err("readline", NULL, strerror(errno)), *exit_status = 1, -1);
		*exit_status = 0;
		return 0;
	}
	if (!ft_memcmp(*content, de, ft_strlen(*content) + 1))
	{
		free(*content);
		*content = NULL;
		*exit_status = 0;
		return 0;
	}
	return 1;
}

static int write_pip(int fd[2], char *content, int *exit_status)
{
	char *line;
	
	line = safe_join(content, "\n");
	free(content);
	content = line;
	if (write(fd[1], content, ft_strlen(content)) == -1)
	{
		free(content);
		print_err("write", NULL, strerror(errno));
		*exit_status = 1;
		return -1;
	}
	*exit_status = 0;
	free(content);
	return 0;
}

int here_doc(char *de, int *exit_status)
{
	int fd[2];
	int status;
	char *content;
	
	
	if (create_pip(fd, exit_status) < 0)
		return -1;
	status = read_here(de, &content, exit_status);
	while (1)
	{
		if (status < 0)
			return (close(fd[0]), close(fd[1]), -1);
		else if (status == 0)
			break ;
		if (write_pip(fd, content, exit_status) < 0)
			return (close(fd[0]), close(fd[1]), -1);
	}
	return (close(fd[1]), fd[0]);
}
