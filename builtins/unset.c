/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 06:55:32 by ewu               #+#    #+#             */
/*   Updated: 2024/12/27 08:11:02 by ewu              ###   ########.fr       */
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

int unset_env(t_env **cpenv, char *arg)
{
	int i;

	i = 0;
	if (valid_input(arg) == false)
		return (1);
	while ((*cpenv)->envar[i])
	{
		if (ft_strncmp((*cpenv)->envar[i], arg, ft_strlen(arg)) == 0)
		{
			del_var(*cpenv, arg);
			break ;
		}
		i++;
	}
	return (0);
}

int ft_unset(char **args, t_env **cpenv, int *exit_status)
{
	int i;

	i = 1;
	if (args_nbr(args) == 1 || !cpenv || !(*cpenv)->envar[0])
		return (1);
	*exit_status = 0;
	while (i < args_nbr(args))
	{
		if (unset_env(cpenv, args[i]))
		{
			*exit_status = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
