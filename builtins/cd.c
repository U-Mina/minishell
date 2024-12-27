/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:39 by ewu               #+#    #+#             */
/*   Updated: 2024/12/27 06:44:57 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * update PWD n' OLDPWD
 * @case: no arg/ abs/relativ path / cd 'wrong input(more than one arg etc)'
 */

static char *cur_path() //check static or not?
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

void cd_dir(t_env *cpenv, int flag)
{
	int i;
	char *tmp;
	char *n_path;
	
	i = 0;
	tmp = cur_path();
	while (i < cpenv->var_nb)
	{
		if (flag == 0 && cpenv->envar[i] && (ft_strncmp(cpenv->envar[i], "OLDPWD", 6) == 0))
		{
			n_path = safe_join("OLDPWD=", tmp);
			free(cpenv->envar[i]);
			cpenv->envar[i] = n_path;
		}
		if (flag == 1 && cpenv->envar[i] && (ft_strncmp(cpenv->envar[i], "PWD", 3) == 0))
		{
			n_path = safe_join("PWD=", tmp);
			free(cpenv->envar[i]);
			cpenv->envar[i] = n_path;
		}
	}
	free(tmp);
}

char *cd_home(t_env *cpenv, int *exit_status)
{
	char *hm;
	
	hm = env_value(cpenv, "HOME");
	if (hm == NULL)
	{
		print_err("minishell", "cd", "HOME not set");
		*exit_status = 1;
		return (NULL);
	}
	*exit_status = 0;
	return (hm);
}

//args here is the token
int ft_cd(char **args, t_env **cpenv, int *exit_status)
{
	int i;
	char *tmp;

	i = 0;
	cd_dir((*cpenv), 0);
	if (args_nbr(args) == 0)
	{
		cd_home((*cpenv), exit_status);
		return (0);	
	}
	tmp = args[0];//the argument from input, from parsing;
	if (chdir(tmp) == -1)
		print_err("minishell: cd", tmp, "No such file or directory");
	else
	{
		free(tmp);
		return (cd_dir((*cpenv), 1), *exit_status = 0, 0);
	}
	free(tmp);
	*exit_status = 1;
	return (1);
}
