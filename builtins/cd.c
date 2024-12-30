/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:39 by ewu               #+#    #+#             */
/*   Updated: 2024/12/30 07:18:39 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * update PWD n' OLDPWD
 * @case: no arg/ abs/relativ path / cd 'wrong input(more than one arg etc)'
 */

static char *cur_path(void) //check static or not?
{
	int i;
	char *tmp;
	char *res;
	
	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
		return (NULL);
	res = safe_malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	i = 0;
	while (tmp[i++])
		res[i] = tmp[i];
	free(tmp);
	res[i] = '\0';
	return (res);
}

void ch_pwd_oldpwd(char **env, int flag)
{
	int i;
	char *tmp;
	char *n_path;
	
	i = 0;
	tmp = cur_path();
	while (i < varlen(env))
	{
		if (flag == 0 && env[i] && (ft_strncmp(env[i], "OLDPWD", 6) == 0))
		{
			n_path = safe_join("OLDPWD=", tmp);
			free(env[i]);
			env[i] = n_path;
		}
		if (flag == 1 && env[i] && (ft_strncmp(env[i], "PWD", 3) == 0))
		{
			n_path = safe_join("PWD=", tmp);
			free(env[i]);
			env[i] = n_path;
		}
	}
	free(tmp);
}

char *cd_home(char **env)
{
	char *hm;
	
	hm = env_value(env, "HOME");
	if (hm == NULL)
	{
		print_err("minishell", "cd", "HOME not set");
		return (NULL);
	}
	return (hm);
}

//args here is the token
int ft_cd(char **args, char ***env)
{
	int i;
	char *tmp;

	i = 0;
	ch_pwd_oldpwd(*env, 0);
	if (args_nbr(args) == 0)
	{
		cd_home(*env);
		return (0);	
	}
	tmp = args[0];//the argument from input, from parsing;
	if (chdir(tmp) == -1)
		print_err("minishell: cd", tmp, "No such file or directory");
	else
	{
		free(tmp);
		return (ch_pwd_oldpwd((*env), 1), 0);
	}
	free(tmp);
	return (1);
}
