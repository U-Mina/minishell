/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:17:26 by ewu               #+#    #+#             */
/*   Updated: 2025/01/25 09:37:57 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * modify ENV wrt:
 * @export: ft_add_env_var (export var=val, '=' needed)
 * @cd: update PWD, OLDPWD
 * @unset: ft_del_env_var
 */

/**
 * EXPORT: search var
 * -> if exit->replace/mod (free)
 * -> if not->add to array (alloc mem)
 */

/**
 * check does a var exist or not
 //idea: to find a var (with/without val)
 */
int	find_env_var(char **env, const char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

//this version is in-place shifting, try another way to create a new **env_arr and free old one
//int	del_var(char ***env, char *key)
int	del_var(char ***env, char *key)
{
	int	i;
	int	pos;
	int	len;

	pos = find_env_var(*env, key);
	len = varlen(*env);
	if (pos < 0)
		return (-2); // no such var
	gc_free((*env)[pos]);
	i = pos;
	while (i < len - 1)
	{
		(*env)[i] = (*env)[i + 1]; //overwrite envar[i]
		i++;
	}
	(*env)[len - 1] = NULL;
	*env = gc_realloc(*env, sizeof(char *) * (len + 1), sizeof(char *) * len);
	return (0);
}

/**
 * cpenv is an array, so everytime new var is added, 
 * new mem_space is needed to put new_var into **cpenv array
 */
static void	put_var(char ***env, char *n_var)
{
	int		i;
	char	**n_env;

	i = varlen(*env);
	n_env = gc_malloc((sizeof(char *) * (i + 2)));
	// if (!n_env)
	// 	return ;
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

//returns an allocated string representing the new env var=val (if any) to include at the env list
char	*create_newvar(const char *key, char *val)
{
	char	*tmp;
	char	*n_var;

	//export cmd without '='/value
	if (val == NULL)
		n_var = gc_strdup(key);
	else
	{
		tmp = gc_strjoin(key, "=");
		n_var = gc_strjoin(tmp, val);
		gc_free(tmp);
	}
	return (n_var);
}

//after any change in env (add/del of var/val), updtae **env array
// flg == true, change to n_val
//the pass para *val is the value to be assign to var
int	update_env(char ***env, const char *key, char *val, bool flg)
{
	int		pos;
	char	*n_var;

	pos = find_env_var(*env, key);
	n_var = create_newvar(key, val);
	if (n_var == NULL)
		return (-1);
	if (pos >= 0)//key does exist
	{
		if (flg == true)
		{
			gc_free((*env)[pos]);
			(*env)[pos] = n_var;
		}
		else
			gc_free(n_var);
		return (0);
	}
	put_var(env, n_var);
	return (0);
}
