/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:07 by ewu               #+#    #+#             */
/*   Updated: 2024/12/30 06:44:12 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @count_env_len: mem allocate
 * @copy_env: 'env' cmd
 * @sort_env: export cmd
 */

// count len of original env, and allocate space accordingly for cpy_env
size_t varlen(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

// hard cp envp vars to **cpenv
char **cpy_env(char **env)
{
	size_t i;
	size_t len;
	char **cpenv;

	i = 0;
	len = varlen(env);
	cpenv = safe_malloc(sizeof(char *) * (len + 1));
	while (i < len)//todo: or make coustomize strdup to check inside??
	{
		cpenv[i] = ft_strdup(env[i]);
		if (!cpenv[i]) //safe check
		{
			while (i-- > 0)
				free(cpenv[i]);
			return (free(cpenv), NULL);
		}
		i++;
	}
	cpenv[i] == NULL;
	return (cpenv);
}

void env_shl(char ***env, char *key)
{
	char *val;
	int pos;

	pos = find_env_var(*env, key);
	free((*env)[pos]);
	val = ft_itoa(ft_atoi(env_value(*env, key) + 1));
	(*env)[pos] = safe_join("SHLVL=", val);//check: is a ;var_create funtion necessary?
	free(val);
}

void chge_pwd(char *oldpwd)
//alphabetical order
void sort_cpenv_var(t_env *cpenv)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (i < cpenv->var_nb - 1)
	{
		j = 0;
		while (j < (cpenv->var_nb - i - 1))
		{
			if (ft_strncmp())
		}
		
	}
}

//ini the struct of t_env, maybe move to *main.c/init.c*
//env = copy of original result of 'env' cmd, and then modify
// t_env *init_cpenv(char **env)
// {
// 	t_env *cpenv;
// 	char **tmp;
// 	size_t i;

// 	i = varlen(env);
// 	cpenv->var_nb = i;
// 	cpenv->envar = cpy_env(env);
// 	return (cpenv);
// }
