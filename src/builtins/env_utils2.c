/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:17:26 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 14:11:18 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// modify ENV wrt: @export, @cd, @unset

//check does a var exist or not, to find a var (with/without val)
int	find_env_var(char **env, const char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '='
			|| env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

// in-place shifting to delete variable from env array
int	del_var(char ***env, char *key)
{
	int	i;
	int	pos;
	int	len;

	pos = find_env_var(*env, key);
	len = varlen(*env);
	if (pos < 0)
		return (-2);
	gc_free((*env)[pos]);
	i = pos;
	while (i < len - 1)
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	(*env)[len - 1] = NULL;
	*env = gc_realloc(*env, sizeof(char *) * (len + 1), sizeof(char *) * len);
	if (!*env)
		return (perror("realloc "), -1);
	return (0);
}

/**
 * cpenv is an array, everytime new var is added,
 * new mem is needed to put new_var into **cpenv array
 */
static void	put_var(char ***env, char *n_var)
{
	int		i;
	char	**n_env;

	i = varlen(*env);
	n_env = gc_malloc((sizeof(char *) * (i + 2)));
	if (!n_env)
		return ;
	i = 0;
	while ((*env)[i])
	{
		n_env[i] = (*env)[i];
		i++;
	}
	n_env[i] = n_var;
	n_env[i + 1] = NULL;
	gc_free(*env);
	*env = n_env;
}

// ret an allocated string representing new env var=val
//(if any) to include at the env list
// if val==NULL, only key is returned, namely export without '='
char	*create_newvar(const char *key, char *val)
{
	char	*tmp;
	char	*n_var;

	if (val == NULL)
	{
		n_var = gc_strdup(key);
		if (n_var == NULL)
			return (NULL);
	}
	else
	{
		tmp = gc_strjoin(key, "=");
		if (tmp == NULL)
			return (NULL);
		n_var = gc_strjoin(tmp, val);
		if (n_var == NULL)
			return (NULL);
		gc_free(tmp);
	}
	return (n_var);
}

// flg == true, change to n_val, false, only add new var without value
// the pass para *val is the value to be assign to var
int	update_env(char ***env, const char *key, char *val, bool flg)
{
	int		pos;
	char	*n_var_with_value;

	pos = find_env_var(*env, key);
	n_var_with_value = create_newvar(key, val);
	if (n_var_with_value == NULL)
		return (-1);
	if (pos >= 0)
	{
		if (flg == true)
		{
			gc_free((*env)[pos]);
			(*env)[pos] = n_var_with_value;
		}
		else
			gc_free(n_var_with_value);
		return (0);
	}
	put_var(env, n_var_with_value);
	return (0);
}
