/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:09:41 by ewu               #+#    #+#             */
/*   Updated: 2024/12/30 08:52:42 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * export =; =val; +=val; =""
 * @1: create cp of env @2: sort cp
 */
 
char *cheapest(char **tmp)
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
		if (ft_strncmp(cheap, tmp[i], ft_strlen(cheap)) > 0) //cheap > tmp[i], swap
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

size_t nonull_varlen(char **env) //count non-null var in env
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
		sorted[i] = cheapest(tmp);
		i++;	
	}
	free(tmp);
	return (sorted);
}
