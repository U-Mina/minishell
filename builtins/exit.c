/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:19:34 by ewu               #+#    #+#             */
/*   Updated: 2024/12/23 16:09:05 by ewu              ###   ########.fr       */
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
void ft_exit(char **args, int *exit_status)
{
	printf("exit\n");
	if (args[1] && !ft_isdigit(args[1]))
	if (args_nbr(args) > 2)
		return (print_err("exit\nminishell", "exit", "too many arguments" ), *exit_status = 1, exit(1));
	if (args_nbr(args) == 1)
		return (*exit_status = 0, exit(0));
	else
		return (*exit_status = 0, exit(ft_atoi(args[1])));
}
