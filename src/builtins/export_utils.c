/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:09:41 by ewu               #+#    #+#             */
/*   Updated: 2025/01/21 13:18:15 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @fn: export cmd without argument, only print alphabetically
 */
//find the smallest alphabetic num/letter
char	*smallest(char **tmp)
{
	int		i;
	int		pos;
	char	*cheap;

	cheap = tmp[0];
	if (varlen(tmp) <= 1)
		tmp[0] = NULL;
	i = 1;
	pos = 0;
	while (tmp[i])
	{
		//cheap > tmp[i], swap
		//if (ft_strncmp(cheap, tmp[i], ft_strlen(cheap)) > 0) 
		if (ft_strncmp(cheap, tmp[i], ft_strlen(cheap) + 1) > 0) 
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
int	nonull_varlen(char **env)
{
	int	i;
	int	j;

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

char	**nonull_cpy(char **env, int len)
{
	int		i;
	int		j;
	char	**nonull;

	nonull = gc_malloc(sizeof(char*) * (len + 1));
	i = 0;
	j = 0;
	while (i < len)
	{
		if (env[i + j] && env[i + j][0])
		{
			nonull[i] = gc_strdup(env[i+j]);
			i++;
		}
		else
			j++;
	}
	nonull[i] = NULL;
	return (nonull);
}

char	**sort_env(char **env, char **sorted)
{
	int		i;
	int		var_nb;
	char	**tmp;

	i = 0;
	var_nb = nonull_varlen(env);
	tmp = nonull_cpy(env, var_nb);
	// need a +1 len for NULL???
	while (i < var_nb)
	{
		sorted[i] = smallest(tmp);
		i++;
	}
	free_double_pointer(tmp);
	return (sorted);
}

int	exp_only(char **env, int *exit_status)
{
	int		i;
	char	**ret_sort;
	char	*sign;

	i = 0;
	ret_sort = gc_malloc(sizeof(char *) * (nonull_varlen(env) + 1));
	// if (!ret_sort)
	// 	return (perror("malloc"), *exit_status = 1, -1);
	ret_sort = sort_env(env, ret_sort);
	//idea: alloc mem for **ret_sort and pass to sorting function
	while (ret_sort[i])
	{
		sign = ft_strchr(ret_sort[i], '=');
		if (sign)
		{
			*sign = '\0';
			printf("declare -x %s=\"%s\"\n", ret_sort[i], sign + 1);
			*sign = '=';
		}
		else
			printf("declare -x %s\n", ret_sort[i]);
		//gc_free(ret_sort[i]); 
		//can just either keep gc_free(ret_sort[i]) or free_double_pointer(ret_sort);
		//not both at the same time!
		i++;
	}
	free_double_pointer(ret_sort);
	*exit_status = 0;
	return (0);
}
