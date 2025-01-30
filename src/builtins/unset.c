/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 06:55:32 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 13:13:03 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char ***env, int *exit_status)
{
	int	i;

	i = 1;
	if (args_nbr(args) == 1 || !env || !env[0])
		return (1);
	*exit_status = 0;
	while (args[i])
	{
		if (valid_unset(args[i]) == false)
			*exit_status = 1;
		else
		{
			if (unset_env(env, args[i]) == -1)
				return (*exit_status = 1, -1);
		}
		i++;
	}
	return (0);
}

bool	valid_unset(char *arg)
{
	int	i;

	if (!arg || !*arg)
	{
		print_err("minishell: unset", "'", "not a valid identifier");
		return (false);
	}
	if (!(ft_isalpha(arg[0]) == 1 || arg[0] == '_'))
	{
		print_err("minishell: unset", arg, "not a valid identifier");
		return (false);
	}
	i = 0;
	while (arg[i] != '\0')
	{
		if (!(ft_isalnum(arg[i]) == 1 || arg[i] == '_'))
		{
			print_err("minishell: unset", arg, "not a valid identifier");
			return (false);
		}
		i++;
	}
	return (true);
}

//break the loop if the var is found and deleted
int	unset_env(char ***env, char *arg)
{
	int	i;
	int	res;

	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, ft_strlen(arg)) == 0
			&& ((*env)[i][ft_strlen(arg)] == '='
				|| (*env)[i][ft_strlen(arg)] == '\0'))
		{
			res = del_var(env, arg);
			if (res == -1)
				return (perror("malloc"), -1);
			break ;
		}
		i++;
	}
	return (0);
}
