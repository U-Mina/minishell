/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 08:53:06 by ewu               #+#    #+#             */
/*   Updated: 2025/01/15 11:42:58 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/**
 * export =; =val; +=val; =""
 */
int ft_export(char ***env, char **args, int *exit_status)
{
	int i;
	
	if (args_nbr(args) == 1)
		exp_only(*env, exit_status);
	*exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (valid_exp(args[i]) == false)
			return (*exit_status = 1, -1);
		if (exp_with_arg(env, args[i]) == -1)
			return (*exit_status = 1, -1);
		i++;
	}
	return (0);
}
