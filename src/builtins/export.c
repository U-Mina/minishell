/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 08:53:06 by ewu               #+#    #+#             */
/*   Updated: 2025/01/24 13:21:04 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * export =; =val; +=val; =""
 */
int	ft_export(char ***env, char **args, int *exit_status)
{
	int	i;

	if (args_nbr(args) == 1)
	{
		//if (exp_only(*env, exit_status) == -1)
		if (exp_only(*env) == -1)
			return (*exit_status = 1, -1);
	}
	*exit_status = 0;
	i = 1;
	while (args[i])
	{
		//return (*exit_status = 1, -1);
		if (exp_with_arg(env, args[i]) == -1)
			return (*exit_status = 1, -1);
		i++;
	}
	return (0);
}
