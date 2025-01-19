/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:17:26 by ewu               #+#    #+#             */
/*   Updated: 2025/01/19 12:58:04 by ewu              ###   ########.fr       */
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

//idea: not exist, create new var and update env
char *create_newvar(const char *key, char *val)
{
	char	*tmp;
	char	*n_var;

	//export cmd without '='/value
	if (val == NULL) 
		n_var = ft_strdup(key);
	else
	{
		tmp = safe_join((char *)key, "=");
		//make "key" not constant char??
		n_var = safe_join(tmp, val);
		free(tmp);
	}
	return (n_var);
}

/**
 * cpenv is an array, so everytime new var is added, 
 * new mem_space is needed to put new_var into **cpenv array
 */
void put_var(char ***env, char *n_var)
{
	int i;
	char **n_env;
	
	i = varlen(*env);
	n_env = ft_realloc(*env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	if (!n_env)
	{
		free(n_env);
		return ;
	}
	n_env[i] = n_var;
	n_env[i + 1] = NULL;
	*env = n_env;
}

void	del_var(char ***env, char *key)
{
	int i;
	int pos;
	int len;
	
	pos = find_env_var(*env, key);
	if (pos < 0)
		return ; // no such var
	free((*env)[pos]);
	len = varlen(*env);
	//cat size_t to int to do comparison??
	i = pos;
	while (i < len - 1)
	{
		(*env)[i] = (*env)[i + 1]; //overwrite envar[i]
		i++;
	}(*env)[len - 1] = NULL;
	*env = ft_realloc(*env, sizeof(char *) * (len
					+ 1), sizeof(char *) * len);
}

//after any change in env (add/del of var/val), updtae **env array
// flg == true, change to n_val
//the pass para *val is the value to be assign to var
int update_env (char ***env, const char *key, char *val, bool flg)
{
	int pos;
	char *n_var;

	pos = find_env_var(*env, key);
	n_var = create_newvar(key, val);//allocate mem for var
	if (n_var == NULL)
		return (-1);
	if (pos >= 0)//key doesnt exist
	{
		if (flg == true)
		{
			free((*env)[pos]);
			(*env)[pos] = n_var;
		}
		else
			free(n_var);
		return (0);
	}
	put_var(env, n_var);
	return (0);
}

// void	update_cpenv(t_env *cpenv, const char *key, char *val)
// {
// 	int		pos;
// 	char	*new_var;

// 	if (!cpenv || !key || !val)
// 		return ;
// 	pos = find_cpenv_var(cpenv, key);
// 	if (pos >= 0)
// 		mod_var(cpenv, val, pos);
// 	else // var doesnt exist
// 	{
// 		new_var = create_var(key, val);
// 		if (!new_var)
// 			return ;
// 		cpenv->envar = ft_realloc(cpenv->envar, sizeof(char *) * (cpenv->var_nb
// 					+ 1), sizeof(char *) * (cpenv->var_nb + 2));
// 		if (!cpenv->envar)//
// 		{
// 			free(new_var);
// 			return ;
// 		}
// 		cpenv->envar[cpenv->var_nb] = new_var;
// 		cpenv->envar[++cpenv->var_nb] = NULL;
// 	}
// }