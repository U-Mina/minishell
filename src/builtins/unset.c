/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 06:55:32 by ewu               #+#    #+#             */
/*   Updated: 2025/01/27 11:07:26 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//debug: when type unset + correct var_name, segfault! with incorrect name, OK!

int	ft_unset(char **args, char ***env, int *exit_status)
{
	int	i;

	i = 1;
	if (args_nbr(args) == 1 || !env || !env[0])
		return (1);
	//*exit_status = 0;
	//while (i < args_nbr(args))
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

//specific str-compare for unset
// static int	unset_cmp(char *unset_var, char *env_var)
// {
// 	int	i;
// 	int	rv;

// 	i = 0;
// 	// if (unset_var == NULL || env_var == NULL)
// 	// 	return -1;
// 	while (unset_var[i] == env_var[i] && unset_var[i] != '\0' && env_var[i] != '\0') // && env_var[i] != '='
// 		i++;
// 	rv = ((unsigned char *)unset_var)[i] - ((unsigned char *)env_var)[i];
// 	return (rv);
// }

//change fali retval from 1 to -1
int	unset_env(char ***env, char *arg)
{
	int	i;
	int	res;

	i = 0;
	//already teted before calling unset_env
	// if (valid_unset(arg) == false)
	// 	return (-1);
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], arg, ft_strlen(arg)) == 0 && ((*env)[i][ft_strlen(arg)] == '=' || (*env)[i][ft_strlen(arg)] == '\0'))
		//if (unset_cmp(arg, (*env)[i]) == 0)
		{
			//check: the del_var() result is not checked, add result check
			res = del_var(env, arg);
			if (res == -1)
			{
				return (perror("malloc"), -1);
			}
			break ;
		}
		i++;
	}
	return (0);
}

// int	unset_env(char ***env, char *arg)
// {
// 	int	i;
// 	int cmp_len;
// 	char *sign;
// 	char *var_2_del;
	

// 	i = 0;
// 	if (valid_unset(arg) == false)
// 		return (-1);
// 	while ((*env)[i])
// 	{
// 		sign = ft_strchr((*env)[i], '=');
// 		if (sign != NULL)
// 		{
// 			cmp_len = sign - (*env)[i];
// 			var_2_del = gc_substr((*env)[i], 0, cmp_len);
// 			if (ft_strncmp(var_2_del, arg, cmp_len) == 0) // len + 1?
// 				del_var(env, i);
// 		}
// 		else
// 		{
// 			if (unset_cmp(arg, (*env)[i]) == 0)
// 			{
// 				//check: the del_var() result is not checked, add result check
// 				int res = del_var(env, i);
// 				if (res == -1)
// 				{
// 					printf("debugging del_var()");
// 					return (print_err("debugging del_var()", NULL, NULL), -1);
// 				}
// 				break ;
// 			}
// 		}
// 		i++;
// 	}
// 	return (0);
// }
