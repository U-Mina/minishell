/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:32:49 by ewu               #+#    #+#             */
/*   Updated: 2025/01/19 16:13:16 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo: use 'args' or 'int* exit_code' as para?
 * or make higher exit_code ft to check retval of each ft: retval (-1)/(0) 
*/
void	ft_pwd(int *exit_status)
{
	char	*cur_dir;

	cur_dir = getcwd(NULL, 0);
	if (cur_dir == NULL)
	{
		perror("getcwd: "); 
	// autmatically format as "getcwd: xxx (error details)"
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