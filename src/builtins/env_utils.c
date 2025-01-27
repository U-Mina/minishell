/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:07 by ewu               #+#    #+#             */
/*   Updated: 2025/01/27 19:49:44 by ipuig-pa         ###   ########.fr       */
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
char	**create_env(void)
{
	char	**env;
	char	*_cwd;
	char	*hm_usr;
	char	*exec_path;

	env = gc_malloc(sizeof(char *) * 6);
	_cwd = getcwd(NULL, 0);
	if (_cwd == NULL)
		return (NULL);
	hm_usr = getenv("HOME");
	if (!hm_usr)
		hm_usr = "/";
	env[0] = gc_strjoin("HOME=", hm_usr);
	env[1] = gc_strjoin("PWD=", _cwd);
	env[2] = gc_strdup("OLDPWD"); //empty at the begining
	env[3] = gc_strjoin("SHLVL=", "1");
	exec_path = gc_strjoin("_=", _cwd);
	env[4] = gc_strjoin(exec_path, "/./minishell");
	env[5] = NULL;
	//use free() or gc_free(), wait for checking
	free(_cwd);
	return (env);
}

// count num of var in env, and allocate mem accordingly for cpy_env
int	varlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

//todo: to change all safe-malloc() to gc_malloc()??
// hard cp **envp vars to **cpenv
char	**cpy_env(char **env)
{
	int		i;
	int		len;
	char	**cpenv;

	i = 0;
	len = varlen(env);
	cpenv = gc_malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		cpenv[i] = gc_strdup(env[i]);
		if (!cpenv[i]) //safe check
		{
			while (i-- > 0)
				gc_free(cpenv[i]);
			return (gc_free(cpenv), NULL);
		}
		i++;
	}
	cpenv[i] = NULL;
	return (cpenv);
}

//key1->"SHLVL", key2->"OLDPWD": shlvl + 1, modify OLDPWD
void	change_shlvl_oldpwd(char ***env, char *key1, char *key2)
{
	char	*val;
	int		pos1;
	int		pos2;

	pos1 = find_env_var(*env, key1);
	// if (pos1 < 0) ??
	//check: the error check necesary or not? just created above
	val = gc_itoa(ft_atoi(env_var_value(*env, key1)) + 1);
	gc_free((*env)[pos1]);
	(*env)[pos1] = gc_strjoin("SHLVL=", val);
	//check: is var_create() funtion necessary?
	gc_free(val);
	pos2 = find_env_var(*env, key2);
	if (pos2 >= 0)
	{
		gc_free((*env)[pos2]);
		(*env)[pos2] = gc_strdup(key2);
	}
	//what to do if OLDPWD is not there?? write also an env variable empty with this name or just not write???
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
