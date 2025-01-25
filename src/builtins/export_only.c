/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_only.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:09:41 by ewu               #+#    #+#             */
/*   Updated: 2025/01/25 11:53:41 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn: export cmd without argument, only print alphabetically
 */

//fomrats the env var list to print
static char	*print_export(char *key)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = gc_malloc(sizeof(char *) * (ft_strlen(key) + 3));//"" + NULL --> 3
	while (key[i])
	{
		tmp[i] = key[i];
		if (key[i] == '=')
		{
			tmp[i + 1] = '\"';
			break ;
		}
		i++;
	}
	i++;
	while (key[i])
	{
		tmp[i + 1] = key[i];
		i++;
	}
	tmp[i + 1] = '"';
	tmp[i + 2] = '\0';
	gc_free(key);
	return (tmp);
}

//find the smallest string (in terms of alphabetic num/letter value) in the env list and returns it
static char	*smallest(char **env_cpy)
{
	int		i;
	int		pos;
	char	*smallest;

	smallest = env_cpy[0];
	if (varlen(env_cpy) <= 1)
		env_cpy[0] = NULL;
	i = 1;
	pos = 0;
	while (env_cpy[i])
	{
		if (ft_strncmp(smallest, env_cpy[i], ft_strlen(smallest) + 1) > 0)
		{
			smallest = env_cpy[i];
			pos = i;
		}
		i++;
	}
	env_cpy[pos] = env_cpy[i - 1];
	env_cpy[i - 1] = NULL;
	return (smallest);
}

//creates and allocates an array of allocated strings containing a copy of env list in data
static char	**copy_env(char **env, int len)
{
	int		i;
	char	**env_cpy;

	env_cpy = gc_malloc((len + 1) * sizeof(char*));
	i = 0;
	while (i < len && env[i] && env[i][0])
	{
		env_cpy[i] = gc_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

//sorts the env var list using a helper copy of env, in which smallest elements are consequently deleted
static void	sort_env(char **env, char ***sorted, int var_nb)
{
	int		i;
	char	**env_cpy;

	i = 0;
	env_cpy = copy_env(env, var_nb);
	while (i < var_nb)
	{
		(*sorted)[i] = smallest(env_cpy);
		i++;
	}
	(*sorted)[i] = NULL;
	gc_free(env_cpy); //do not double free, because otherwise we lost the allocated strings, now stored in the sorted double string.
}

//sorts the list of env var, formats it to print and prints it
int	exp_only(char **env)
{
	int		i;
	char	**sorted_env;
	int		var_len;

	i = 0;
	var_len = varlen(env);
	sorted_env = gc_malloc(sizeof(char *) * (var_len + 1));
	// if (!sorted_env)
	// 	return (perror("malloc"), *exit_status = 1, -1);
	sort_env(env, &sorted_env, var_len);
	while (sorted_env[i])
	{
		sorted_env[i] = print_export(sorted_env[i]);
		printf("declare -x %s\n", sorted_env[i]);
		i++;
	}
	free_double_pointer(sorted_env);
	return (0);
}
