/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 08:53:06 by ewu               #+#    #+#             */
/*   Updated: 2025/01/19 16:11:24 by ipuig-pa         ###   ########.fr       */
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
