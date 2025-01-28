/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 17:12:30 by ewu               #+#    #+#             */
/*   Updated: 2025/01/28 19:25:25 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn: export with args & values
 */

//returns an allocated string, being a copy of the passed str with a \ added before each conflictive character (" and \")
static void	add_escape_char(char **n_val, char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\\')
			count++;
		i++;
	}
	*n_val = gc_malloc((ft_strlen(str) + count + 1) * sizeof(char));
	while (i >= 0)
	{
		(*n_val)[i + count] = str[i];
		if (str[i] == '\"' || str[i] == '\\')
		{
			count--;
			(*n_val)[i + count] = '\\';
		}
		i--;
	}
}

//grammar checks the env var name(but not to apply to the env var value)
static bool	valid_exp(char *arg)
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

//export with '=' sign
static int	withsign(char ***env, char *arg, char *sign)
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
	add_escape_char(&n_val, sign + 1);
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
static int	nosign(char ***env, char *arg)
{
	char	*n_key;

	n_key = arg;
	if (find_env_var(*env, n_key) == -1)
	{
		if (!valid_exp (arg))
			return (-1);
		if (update_env(env, n_key, NULL, false) != 0)
			return (perror("malloc fail"), -1);
	}
	return (0);
}

//wrap fn for case choose
int	exp_with_arg(char ***env, char *arg)
{
	char	*sign;
	int		res;

	sign = ft_strchr(arg, '=');
	if (sign != NULL && sign != arg)
		res = withsign(env, arg, sign);
	else
		res = nosign(env, arg);
	return (res);
}
