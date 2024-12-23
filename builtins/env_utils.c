/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:18:07 by ewu               #+#    #+#             */
/*   Updated: 2024/12/20 13:01:12 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @count_env_len: mem allocate
 * @copy_env: 'env' cmd
 * @sort_env: export cmd
 */

// count len of original env, and allocate space according for cpy_env
int varlen(char **env)
{
	int i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

// hard cp envp vars to **cpenv
char **cpy_env(char **envp)
{
	int i;
	int len;
	char **cpenv;

	len = varlen(envp);
	cpenv = safe_malloc(sizeof(char *) * (len + 1));
	// cpenv = (char **)malloc(sizeof(char *) * (len + 1));
	// if (cpenv == NULL)
	// {
	// 	perror("malloc: ");
	// 	return (-1);//todo: or use exit_status flag (1)? (mimic how bash works)
	// }
	i = 0;
	while (i < len)//todo: or make coustomize strdup to check inside??
	{
		cpenv[i] = ft_strdup(envp[i]);
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

//ini the struct of t_env
//env = copy of original result of 'env' cmd, and then modify
t_env *init_env(char **envp)
{
	t_env *cpenv;

	cpenv = safe_malloc(sizeof(t_env));
	cpenv->envar = cpy_env(envp);
	cpenv->var_nb = varlen(envp);
	return (cpenv);
}

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
