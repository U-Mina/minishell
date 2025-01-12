/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:07 by ewu               #+#    #+#             */
/*   Updated: 2025/01/11 13:09:40 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @count_env_len: mem allocate
 * @copy_env: 'env' cmd
 * @sort_env: export cmd
 */

//if no env var is passed, create a var list for it
//HOME, PWD, OLDPWD, SHLVL, _=, NULL
//check: ?? to add executable path
char **create_env(void)
{
	char **env;
	char *_cwd;
	char *hm_usr;
	char *exec_path;
	
	env = safe_malloc(sizeof(char *) * 6);
	// _cwd = getcwd(NULL, 0);
	// if (_cwd == NULL)
	// 	return NULL;
	_cwd = cur_path();
	hm_usr = getenv("HOME");
	if (!hm_usr)
		hm_usr = "/";
	env[0] = safe_join("HOME=", hm_usr);
	env[1] = safe_join("PWD=", _cwd);
	env[2] = ft_strdup("OLDPWD"); //empty at the begining
	env[3] = safe_join("SHLVL=", "1");
	exec_path = safe_join("_=", _cwd);
	env[4] = safe_join(exec_path, "/./minishell");
	env[5] = NULL;
	free(_cwd);
	return (env);
}

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

//key1->"SHLVL", key2->"OLDPWD"
void change_shlvl_oldpwd(char ***env, char *key1, char *key2)
{
	char *val;
	char *var_pwd;
	int pos1;
	int pos2;

	var_pwd = NULL;
	pos1 = find_env_var(*env, key1);
	// if (pos1 < 0) ??
	//check: the error check necesary or not? just created above
	free((*env)[pos1]);
	val = ft_itoa(ft_atoi(env_value(*env, key1) + 1));
	(*env)[pos1] = safe_join("SHLVL=", val);//check: is a ;var_create funtion necessary?
	free(val);
	pos2 = find_env_var(*env, key2);
	free((*env)[pos2]);
	(*env)[pos2] = ft_strdup(key2);
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
