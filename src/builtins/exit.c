/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:19:34 by ewu               #+#    #+#             */
/*   Updated: 2025/01/25 14:44:58 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * end cur shell, clean everything
 * no arg, nbr args, word args
 */

//to coustomize ft_isdigit() to pass string instead int as para
static int	is_digit(char *s)
{
	while (*s)
	{
		if (!(*s >= '0' && *s <= '9'))
			return (-1);
		s++;
	}
	return (0);
}

void ft_exit(t_data *data, char **args)
{
	printf("exit\n");
	if (args_nbr(args) > 2)
	{
		print_err("minishell", "exit", "too many arguments");
		data->exit_status = 1;
		return ;
	}
	if (args_nbr(args) == 2)
	{
		if (is_digit(args[1]) == 0)
		{
			data->exit_status = ft_atoi(args[1]);
			term_minishell(data->minishell, ft_atoi(args[1]));
		}
		else if (is_digit(args[1]) == -1)
		{
			print_err("minishell", args[1], "numeric argument required");
			data->exit_status = 255;
			term_minishell(data->minishell, 255);
		}
	}
	data->exit_status = 0;
	term_minishell(data->minishell, 0);
}
		
// void ft_exit(char **args, int *exit_status)
// {
// 	printf("exit\n");
// 	if (args_nbr(args) > 1)
// 	{
// 		if (is_digit(args[1]) == -1)
// 		{
// 			print_err("minishell", args[1], "numeric argument required" );
// 			*exit_status = 255;
// 			exit(*exit_status);
// 		}
// 		else
// 		{
// 			if (args_nbr(args) == 2)
// 			{
// 				*exit_status = ft_atoi(args[1]);
// 				exit(*exit_status);
// 			}
// 			else
// 			{
// 				print_err("minishell", "exit", "too many arguments" );
// 				*exit_status = 1;
// 			}
// 		}
// 	}
// 	else
// 		exit(0);
// }
