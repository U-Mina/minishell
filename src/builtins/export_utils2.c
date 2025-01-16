/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:12:30 by ewu               #+#    #+#             */
/*   Updated: 2025/01/16 13:09:00 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//grammar check
bool valid_exp(const char *arg)
{
	int i;
	
	if (!arg || !*arg)
		return (false);
	if (!(ft_isalpha(arg[0]) == 1 || arg[0] == '_'))
	{
		print_err("minishell: export", arg, "not a valid identifier");
		return (false);	
	}
	i = 1;
	while (arg[i] && arg[i] != '=')
	{
		if (!(ft_isalnum(arg[i]) == 1 || arg[i] == '_'))
		{
			print_err("minishell: export", arg, "not a valid identifier");
			return (false);
		}
		i++;
	}
	return (true);
}

/**
 * @fn: export with args & values
 */
//wrap fn for case choose
int exp_with_arg(char ***env, char *arg)
{
	char *sign;
	int res;

	sign = ft_strchr(arg, '=');
	if (sign)
		res = withsigh(env, arg, sign);
	else
		res = nosign(env, arg);
	return (res);
}

//export with '=' sign
int withsigh(char ***env, char *arg, char *sign)
{
	size_t len;
	char *n_key;
	char *n_val;

	len = sign - arg;
	n_key = safe_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(n_key, arg, len + 1);
	n_val = ft_strdup(sign + 1);
	if (!n_key || !n_val)
		return (perror("malloc fail"), -1);
	if (update_env(env, n_key, n_val, true) != 0)
		return (perror("malloc fail"), -1);
	free(n_key);
	free(n_val);
	return (0);
}

//export without '=' sign
int nosign(char ***env, char *arg)
{
	char *n_key;
	
	n_key = arg;
	if (find_env_var(*env, n_key) == -1)
	{
		if (update_env(env, n_key, NULL, false) == -1)
			return (perror("malloc fail"), -1);
	}
	return (0);
}
