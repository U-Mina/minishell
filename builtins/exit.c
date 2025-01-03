/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:19:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/01 20:28:13 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * end cur shell, clean everything
 * no arg, nbr args, word args
 */

/**
 * @args: array of passed args, based on pasrsing
*/

//check: handle 'args[1]:' print, or ft_exit_status?
void ft_exit(char **args)
{
	printf("exit\n");
	if (args_nbr(args) > 1)
	{
		if (!ft_isdigit(args[1]))
		{
			print_err("minishell", args[1], "numeric argument required" );
			exit(255);
		}
		else
		{
			if (args_nbr(args) == 2)
				exit(ft_atoi(args[1]));
			else
			{
				print_err("minishell", "exit", "too many arguments" );
				exit(1);
			}
		}
	}
	else
		exit(0);
}
