/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:32:49 by ewu               #+#    #+#             */
/*   Updated: 2025/01/01 20:03:11 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * todo: use 'args' or 'int* exit_code' as para?
 * or make higher exit_code ft to check retval of each ft: retval (-1)/(0) 
*/
void ft_pwd(void)
{
	char *cur_dir;
	
	cur_dir = getcwd(NULL, 0);
	if (cur_dir == NULL)
		perror("getcwd: "); // autmatically format as "getcwd: xxx (error details)"
	printf("%s\n", cur_dir);
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