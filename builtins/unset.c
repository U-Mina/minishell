/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 06:55:32 by ewu               #+#    #+#             */
/*   Updated: 2024/12/30 07:15:35 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * del the var/val added by 'export', update *cpenv
 */

bool valid_input(const char *arg)
{
	int i;
	
	if (!arg || !*arg)
		return (false);
	if (!(ft_isalpha(arg[0]) == 1 || arg[0] == '_'))
	{
		print_err("minishell: unset", arg, "not a valid identifier");
		return (false);	
	}
	i = 1;
	while (arg[i++])
	{
		if (!(ft_isalnum(arg[i]) == 1 || arg[i] == '_'))
		{
			print_err("minishell: unset", arg, "not a valid identifier");
			return (false);
		}
	}
	return (true);
}

int unset_env(char ***env, char *arg)
{
	int i;

	i = 0;
	if (valid_input(arg) == false)
		return (1);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, ft_strlen(arg)) == 0)
		{
			del_var(env, arg);
			break ;
		}
		i++;
	}
	return (0);
}

int ft_unset(char **args, char ***env)
{
	int i;

	i = 1;
	if (args_nbr(args) == 1 || !env || !(*env)[0])
		return (1);
	while (i < args_nbr(args))
	{
		if (unset_env(*env, args[i]))
			return (1);
		i++;
	}
	return (0);
}
