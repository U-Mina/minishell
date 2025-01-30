/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:07 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 14:06:09 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @copy_env: 'env' cmd
 * @sort_env: export cmd
 */

//if no env var is passed, create: HOME, PWD, OLDPWD, SHLVL, _=, NULL
char	**create_env(void)
{
	char	**env;
	char	*_cwd;
	char	*hm_usr;
	char	*exec_path;

	env = gc_malloc(sizeof(char *) * 6);
	if (!env)
		return (perror("malloc "), NULL);
	_cwd = getcwd(NULL, 0);
	if (_cwd == NULL)
		return (NULL);
	hm_usr = getenv("HOME");
	if (!hm_usr)
		hm_usr = "/";
	env[0] = gc_strjoin("HOME=", hm_usr);
	env[1] = gc_strjoin("PWD=", _cwd);
	env[2] = gc_strdup("OLDPWD");
	env[3] = gc_strjoin("SHLVL=", "1");
	exec_path = gc_strjoin("_=", _cwd);
	env[4] = gc_strjoin(exec_path, "/./minishell");
	env[5] = NULL;
	gc_free(exec_path);
	free(_cwd);
	return (env);
}

// count nbr of var in env, and alloc mem accordingly for cpy_env
int	varlen(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

// hard copy of **envp
// if any malloc error, free all the previous malloced mem
char	**cpy_env(char **env)
{
	int		i;
	int		len;
	char	**cpenv;

	i = 0;
	len = varlen(env);
	cpenv = gc_malloc(sizeof(char *) * (len + 1));
	if (!cpenv)
		return (perror("malloc "), NULL);
	while (i < len)
	{
		cpenv[i] = gc_strdup(env[i]);
		if (!cpenv[i])
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

/**
 * @key1: SHLVL, @key2: OLDPWD; shlvl + 1, modify OLDPWD
 * If shlvl/oldpwd doesn't exist in the env,it adds them with values*/
void	change_shlvl_oldpwd(char ***env, char *key1, char *key2)
{
	char	*val;
	int		pos1;
	int		pos2;

	pos1 = find_env_var(*env, key1);
	if (pos1 >= 0)
	{
		val = gc_itoa(ft_atoi(env_var_value(*env, key1)) + 1);
		if (val == NULL)
			return ;
		gc_free((*env)[pos1]);
		(*env)[pos1] = gc_strjoin("SHLVL=", val);
		gc_free(val);
	}
	else
		update_env(env, key1, "1", true);
	pos2 = find_env_var(*env, key2);
	if (pos2 >= 0)
	{
		gc_free((*env)[pos2]);
		(*env)[pos2] = gc_strdup(key2);
	}
	else
		update_env(env, key2, "", true);
}
