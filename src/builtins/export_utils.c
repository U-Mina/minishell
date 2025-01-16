/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:09:41 by ewu               #+#    #+#             */
/*   Updated: 2025/01/16 13:08:56 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn: export cmd without argument, only print alphabetically
 */
//find the smallest alphabetic num/letter
char *smallest(char **tmp)
{
	int i;
	int pos;
	char *cheap;

	cheap = tmp[0];
	if (varlen(tmp) <= 1)
		tmp[0] = NULL;
	i = 0;
	pos = 0;
	while (tmp[i])
	{
		if (ft_strncmp(cheap, tmp[i], ft_strlen(cheap)) > 0) 
		//cheap > tmp[i], swap
		{
			cheap = tmp[i];
			pos = i;
		}
		i++;
	}
	tmp[pos] = tmp[i - 1];
	tmp[i - 1] = NULL;
	return (cheap);
}

//count non-null var in env (with a value and '=' sign)
size_t nonull_varlen(char **env)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < varlen(env))
	{
		if (env[i] == NULL)
			j++;
		i++;
	}
	return (i - j);
}

char **nonull_cpy(char **env, size_t len)
{
	size_t i;
	size_t j;
	char **nonull;

	nonull = safe_malloc(sizeof(char*) * (len + 1));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (env[i + j] && env[i + j][0])
		{
			nonull[i] = ft_strdup(env[i+j]);
			i++;
		}
		else
			j++;
	}
	return (nonull[i] = NULL);
}

char **sort_env(char **env)
{
	size_t i;
	size_t var_nb;
	char **tmp;
	char **sorted;

	i = 0;
	var_nb = nonull_varlen(env);
	tmp = nonull_cpy(env, var_nb);
	while (i < var_nb)
	{
		sorted[i] = smallest(tmp);
		i++;	
	}
	free(tmp);
	return (sorted);
}

int exp_only(char **env, int *exit_status)
{
	int i;
	char **sorted;
	char *sign;

	i = 0;
	sorted = sort_env(env);
	if (!sort_env)
		return (perror("malloc"), *exit_status = 1, -1);
	while (sorted[i])
	{
		sign = ft_strchr(sorted[i], '=');
		if (sign)
		{
			*sign = '\0';
			printf("declare -x %s=\"%s\"\n", sorted[i], sign + 1);
			*sign = '=';
		}
		else
			printf("declare -x %s\n", sorted[i]);
		free(sorted[i]);
		i++;
	}
	free(sorted);
	*exit_status = 0;
	return (0);
}
