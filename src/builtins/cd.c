/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:39 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 13:48:28 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * cases: no arg/abosolute/relativ path/cd 'wrong input(more than one arg etc)'
 */

// actul exec part of changing directory
bool	check_err_go_dir(char *path, int *exit_status)
{
	if (access(path, F_OK) != 0)
	{
		print_err("minishell: cd", path, "No such file or directory");
		return (*exit_status = 1, false);
	}
	if (chdir(path) != 0)
	{
		if (errno == ENOTDIR)
			print_err("minishell: cd", path, "Not a directory");
		else if (errno == EACCES)
			print_err("minishell: cd", path, "Permission denied");
		else
			print_err("minishell: cd", path, "No such file or directory");
		*exit_status = 1;
		return (false);
	}
	*exit_status = 0;
	return (true);
}

// get current path
char	*cur_path(void)
{
	int		i;
	char	*tmp;
	char	*res;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("gercwd: ");
		return (NULL);
	}
	res = gc_malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	if (!res)
	{
		perror("malloc ");
		return (NULL);
	}
	i = 0;
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	free(tmp);
	res[i] = '\0';
	return (res);
}

// change to home directory (call check_err_go_dir() to exec)
bool	cd_home(char **env, int *exit_status)
{
	char	*hm;

	hm = env_var_value(env, "HOME");
	if (hm == NULL)
	{
		print_err("minishell", "cd", "HOME not set");
		*exit_status = 1;
		return (false);
	}
	return (check_err_go_dir(hm, exit_status));
}

// args[0] = "cd", args[1] = path
// if no path, go to home directory, else go to path
int	ft_cd(char **args, char ***env, int *exit_status)
{
	char	*cur;
	bool	retval;

	cur = cur_path();
	if (cur == NULL)
		return (*exit_status = 1, -1);
	if (args_nbr(args) == 1)
		retval = cd_home(*env, exit_status);
	else
		retval = check_err_go_dir(args[1], exit_status);
	if (retval == true)
		return (handle_pwd(cur, env), 0);
	*exit_status = 1;
	return (-1);
}

// update PWD and OLDPWD after successful cd
// if OLDPWD doesn't exist, create one, else update PWD and OLDPWD
void	handle_pwd(char *o_pwd, char ***env)
{
	char	*new_cur;
	char	*new_var;

	new_cur = cur_path();
	if (new_cur == NULL)
	{
		perror("getcwd: ");
		return ;
	}
	if (find_env_var(*env, "OLDPWD") < 0)
	{
		new_var = create_newvar("OLDPWD", o_pwd);
		if (new_var == NULL)
		{
			perror("create_newvar: ");
			return ;
		}
		update_env(env, "OLDPWD", new_var, true);
	}
	else
		update_env(env, "OLDPWD", o_pwd, true);
	update_env(env, "PWD", new_cur, true);
}
