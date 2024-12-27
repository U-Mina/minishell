/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:17:26 by ewu               #+#    #+#             */
/*   Updated: 2024/12/27 07:42:06 by ewu              ###   ########.fr       */
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

//check does a var exist or not
//idea: this is the case with value & '=' sign?
int	find_cpenv_var(t_env *cpenv, const char *key)
{
	int	i;
	int	len;

	if (!cpenv || !key)
		return (-1);
	i = 0;
	len = ft_strlen(key);
	while (i < cpenv->var_nb)
	{
		if (cpenv->envar[i] && ft_strncmp(cpenv->envar[i], key, ft_strlen(key)) == 0
			&& (cpenv->envar[i][len] == '=' || cpenv->envar[i][len] == '\0'))
			return (i);
		i++;
	}
	return (-1);
}

//idea: update t_env (add or modify or delete)
void	update_cpenv(t_env *cpenv, const char *key, char *val)
{
	int		pos;
	char	*new_var;

	if (!cpenv || !key || !val)
		return ;
	pos = find_cpenv_var(cpenv, key);
	if (pos >= 0)
		mod_var(cpenv, val, pos);
	else // var doesnt exist
	{
		new_var = create_var(key, val);
		if (!new_var)
			return ;
		cpenv->envar = ft_realloc(cpenv->envar, sizeof(char *) * (cpenv->var_nb
					+ 1), sizeof(char *) * (cpenv->var_nb + 2));
		if (!cpenv->envar)//
		{
			free(new_var);
			return ;
		}
		cpenv->envar[cpenv->var_nb] = new_var;
		cpenv->envar[++cpenv->var_nb] = NULL;
	}
}

//idea: not exist, create new var
char	*create_var(const char *key, char *val)
{
	char	*tmp;
	char	*n_var;

	if (val == NULL) //export cmd without '='/value
		n_var = ft_strdup(key);
	else
	{
		tmp = safe_join(key, "=");
		n_var = safe_join(tmp, val);
		free(tmp);
	}
	return (n_var);
}

//idea: exist, modify var & value
//debug: malloc and mempry need to be checked!
void	mod_var(t_env *cpenv, char *new_val, int pos)
{
	char	*var;
	//char	*tmp;

	var = create_var(cpenv->envar[pos], new_val);
	if (!var)
		return (NULL);
	free(cpenv->envar[pos]);
	cpenv->envar[pos] = var;
}

void	del_var(t_env *cpenv, char *key)
{
	int i;
	int pos;
	
	if (!cpenv || !key)
		return ;
	pos = find_cpenv_var(cpenv, key);
	if (pos < 0)
		return ; // no such var
	free(cpenv->envar[pos]);
	i = pos;
	while (i < cpenv->var_nb - 1)
	{
		cpenv->envar[i] = cpenv->envar[i + 1]; //overwrite envar[i]
		i++;
	}
	cpenv->envar = ft_realloc(cpenv->envar, sizeof(char *) * (cpenv->var_nb
					+ 1), sizeof(char *) * (cpenv->var_nb));
	cpenv->var_nb--;
	//todo: check is it necessary to call update_env after del!
}

// void	mod_cpenv_value(t_env *cpenv, char *key, char *val)
// {
// }
// void	del_cpenv_value(t_env *cpenv, char *key, char *val)