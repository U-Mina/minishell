/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:32:49 by ewu               #+#    #+#             */
/*   Updated: 2025/01/21 11:43:41 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//perror("getcwd: "): autmatically format as "getcwd: xxx (error details)"
void	ft_pwd(int *exit_status)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (cur_dir == NULL)
	{
		perror("getcwd: "); 
		*exit_status = 1;
	}
	printf("%s\n", cur_dir);
	*exit_status = 0;
	free(cur_dir);
}

// case(arg)
// strncmp(==0)
// execute_buildin( struct ){
// 	pwd();
// 	if ( pwd() == -1)
// 		struct->exit_status = 1;
// 	cd;
	
// }

// execve( args )
// if == , exit_ = 127;

// if eixt 

// 127;