/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 15:35:39 by ewu               #+#    #+#             */
/*   Updated: 2025/01/21 11:28:32 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * update PWD n' OLDPWD
 * @case: no arg/ abs/relativ path / cd 'wrong input(more than one arg etc)'
 */
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
		return (*exit_status = 1, false);
	}
	*exit_status = 0;
	return	(true);
}
// if (access(path, X_OK) != 0)
// {
// 	print_err("minishell: cd", path, "Permission denied");
// 	return (*exit_status = 1, false);
// }

char	*cur_path(int *exit_status)
{
	int		i;
	char	*tmp;
	char	*res;

	tmp = getcwd(NULL, 0);
	if (tmp == NULL)
	{
		perror("gercwd: ");
		*exit_status = 1;
		return (NULL);
	}
	res = gc_malloc(sizeof(char) * (ft_strlen(tmp) + 1));
	i = 0;
	while (tmp[i])
	{
		res[i] = tmp[i];
		i++;
	}
	free(tmp);
	res[i] = '\0';
	*exit_status = 0;
	return (res);
}

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
	//*exit_status = 0;
	return (check_err_go_dir(hm, exit_status));
}
// return (hm);

int	ft_cd(char **args, char ***env, int *exit_status)
{
	//int		i;
	char	*cur;
	bool	retval;

	cur = cur_path(exit_status);
	if (cur == NULL)
		return (-1);
	if (args_nbr(args) == 1) //only 'cd' cmd
		retval = cd_home(*env, exit_status);
	else
		retval = check_err_go_dir(args[1], exit_status);
	if (retval == true)
		return (handle_pwd(cur, env, exit_status), 0);//change pwd and old after success, err checked needed later
	return (-1);
}

void	handle_pwd(char *o_pwd, char ***env, int *exit_status)
{
	char	*cur;
	char	*n_var;

	cur = cur_path(exit_status);
	if (find_env_var(*env, "OLDPWD") < 0)//no OLDPWD exist, create one
	{
		n_var = create_newvar("OLDPWD", o_pwd);
		// put_var(env, n_var);
		//check: error check needed??
		update_env(env, "OLDPWD", n_var, true);
	}
	else//OLDPWD exist, change it to o_pwd
		update_env(env, "OLDPWD", o_pwd, true);
	update_env(env, "PWD", cur, true);
}

//in this way avoid possible seg-fault problem
// void	cur_path(char cur[PATH_MAX], int *exit_status)
// {
// 	if (getcwd(cur, sizeof(cur)) == NULL)
// 	{
// 		perror("gercwd: ");
// 		*exit_status = 1;
// 		return (NULL);
// 	}
// 	*exit_status = 0;
// }

	// tmp = args[1];
	// if (chdir(tmp) == -1)
	// {
	// 	print_err("minishell: cd", tmp, "No such file or directory");
	// 	*exit_status = 1;
	// }
	// else
	// {
	// 	free(tmp);
	// 	return (ch_pwd_oldpwd((*env), 1, exit_status), 0);
	// }
	// free(tmp);
	// return (1);

// char	*cur_path(int *exit_status)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*res;
// 	tmp = getcwd(NULL, 0);
// 	if (tmp == NULL)
// 	{
// 		perror("gercwd: ");
// 		*exit_status = 1;
// 		return (NULL);
// 	}
// 	res = gc_malloc(sizeof(char) * (ft_strlen(tmp) + 1));
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		res[i] = tmp[i]; //not sure if this will give seg fault...??
// 		i++;	
// 	}
// 	free(tmp);
// 	res[i] = '\0';
// 	*exit_status = 0;
// 	return (res);
// }

// void	ch_pwd_oldpwd(t_data *data, int flag)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*n_path;

// 	i = 0;
// 	tmp = cur_path(data->exit_status);
// 	while (i < varlen(data->env))
// 	{
// 		if (flag == 0 && data->env[i] && (ft_strncmp(data->env[i], "OLDPWD", 7) == 0))
// 		{
// 			n_path = safe_join("OLDPWD=", tmp);
// 			free(data->env[i]);
// 			data->env[i] = n_path;
// 		}
// 		if (flag == 1 && data->env[i] && (ft_strncmp(data->env[i], "PWD", 4) == 0))
// 		{
// 			n_path = safe_join("PWD=", tmp);
// 			free(data->env[i]);
// 			data->env[i] = n_path;
// 		}
// 		i++;
// 	}
// 	free(tmp);
// }
// char	*cd_home(char **env, int *exit_status)
// {
// 	char	*hm;

// 	hm = env_var_value(env, "HOME");
// 	if (hm == NULL)
// 	{
// 		print_err("minishell", "cd", "HOME not set");
// 		*exit_status = 1;
// 		return (NULL);
// 	}
// 	*exit_status = 0;
// 	return (hm);
// }

// void	ch_pwd_oldpwd(char **env, int flag, int *exit_status)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*n_path;

// 	i = 0;
// 	tmp = cur_path(exit_status);
// 	while (i < varlen(env))
// 	{
// 		if (flag == 0 && env[i] && (ft_strncmp(env[i], "OLDPWD", 6) == 0))
// 		{
// 			n_path = safe_join("OLDPWD=", tmp);
// 			free(env[i]);
// 			env[i] = n_path;
// 		}
// 		if (flag == 1 && env[i] && (ft_strncmp(env[i], "PWD", 3) == 0))
// 		{
// 			n_path = safe_join("PWD=", tmp);
// 			free(env[i]);
// 			env[i] = n_path;
// 		}
// 		i++;
// 	}
// 	free(tmp);
// }
