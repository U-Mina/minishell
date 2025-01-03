/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 08:53:06 by ewu               #+#    #+#             */
/*   Updated: 2025/01/01 20:00:29 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * export =; =val; +=val; =""
 */

int ft_export(char ***env, char **args)
{
	int i;
	
	if (args_nbr(args) == 1)
		exp_only(*env);
	else
	{
		i = 1;
		while (args[i])
		{
			if (valid_exp(args[i]) == false)
				return (-1);
			if (exp_arg(env, args[i]) == -1)
				return (-1);
			i++;
		}
	}
	return (0);
}
