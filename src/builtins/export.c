/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 08:53:06 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 13:02:03 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @cases: export=; export=val; export=""
 */
int	ft_export(char ***env, char **args, int *exit_status)
{
	int	i;

	if (args_nbr(args) == 1)
	{
		if (exp_only(*env) == -1)
			return (*exit_status = 1, -1);
	}
	else
	{
		i = 1;
		while (args[i])
		{
			if (exp_with_arg(env, args[i]) == -1)
				return (*exit_status = 1, -1);
			i++;
		}
	}
	return (0);
}
