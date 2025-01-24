/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:12:30 by ewu               #+#    #+#             */
/*   Updated: 2025/01/24 13:20:33 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//grammar check
//idea: change para from 'const char *arg' to 'char *arg'
bool	valid_exp(char *arg)
{
	int	i;

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
int	exp_with_arg(char ***env, char *arg)
{
	char	*sign;
	int		res;

	sign = ft_strchr(arg, '=');
	if (sign != NULL)
		res = withsign(env, arg, sign);
	else
		res = nosign(env, arg);
	return (res);
}

// static char	*handle_quotes(char *str)
// {
// 	char	*res;
// 	int		i;
// 	int		j;
// 	char	quote;

// 	i = 0;
// 	j = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'' || str[i] == '\"')

// 			i = i + quote_len(str, i);
// 		if (str[i] != '\'' && str[i] != '\"')
// 			j++;
// 		i++;
// 	}
// 	res = gc_malloc(j * sizeof(char));
// 	while (i >= 0)
// 	{
// 		if (str[i] != '\'' && str[i] != '\"')
// 		{
// 			res[j] = str[i];
// 			j--;
// 		}
// 		i--;
// 	}
// 	gc_free(str);
// 	return (res);
// }

//export with '=' sign
int	withsign(char ***env, char *arg, char *sign)
{
	size_t	len;
	char	*n_key;
	char	*n_val;

	len = sign - arg;
	n_key = gc_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(n_key, arg, len + 1);
	if (valid_exp(n_key) == false)
	{
		gc_free(n_key);
		return (-1);
	}
	n_val = gc_strdup(sign + 1);
	if (n_key != NULL && n_val != NULL)
	{
		if (update_env(env, n_key, n_val, true) != 0)
			return (perror("malloc fail"), -1);
	}
	else
		return (perror("malloc fail"), -1);
	gc_free(n_key);
	gc_free(n_val);
	return (0);
}

//export without '=' sign
int	nosign(char ***env, char *arg)
{
	char	*n_key;

	n_key = arg;
	if (find_env_var(*env, n_key) == -1)
	{
		if (update_env(env, n_key, NULL, false) != 0)
			return (perror("malloc fail"), -1);
	}
	return (0);
}

char	*print_export(char *key)
{
	int i;
	char	*retval;

	i = 0;
	retval = gc_malloc(sizeof(char *) * (ft_strlen(key) + 3));//"" + NULL --> 3
	while (key[i])
	{
		retval[i] = key[i];
		if (key[i] == '=')
		{
			retval[i + 1] = '"';
			break ;
		}
		i++;
	}
	i = i + 1;
	while (key[i])
	{
		retval[i + 1] = key[i];
		i++;
	}
	retval[i + 1] = '"';
	retval[i + 2] = '\0';
	//free(key);
	return (retval);
}
