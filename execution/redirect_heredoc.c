/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 22:45:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/15 12:45:15 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static char *read_here(char *de, int *exit_status)
{
	char *content;
	char *retval;
	
	content = readline("> ");
	if (!content || !ft_memcmp(content, de, ft_strlen(*content) + 1)) 
	{
		if (errno != 0)
			return (print_err("readline", NULL, strerror(errno)), *exit_status = 1, NULL);
		free(content);
		content = NULL;
		*exit_status = 0;
		return NULL;
	}
	//here to add '$' sign handler
	retval = safe_join(content, "\n");
	free(content);
	return (retval);
}

static int write_pip(int fd[2], char *retval, int *exit_status)
{
	if (write(fd[1], retval, ft_strlen(retval)) == -1)
	{
		free(retval);
		print_err("write", NULL, strerror(errno));
		*exit_status = 1;
		return -1;
	}
	*exit_status = 0;
	free(retval);
	return 0;
}

int here_doc(char *de, int *exit_status)
{
	int fd[2];
	int status;
	char *line;
	
	if (create_pip(fd, exit_status) < 0)
		return -1;
	while (1)
	{
		line = read_here(de, exit_status);
		if (line == NULL)//finished reading(EOF) or meet delim
			break ;
		if (write_pip(fd, line, exit_status) < 0)
		{
			free(line);
			return (close(fd[0]), close(fd[1]), -1);
		}
	}
	close(fd[1]);
	return (fd[0]);
}
