/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:45:08 by ewu               #+#    #+#             */
/*   Updated: 2024/12/27 05:04:46 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * get the value of env var
 */

char *env_value(t_env *cpenv, const char *key)
{
	int i;
	int len;
	
	if (!cpenv || !key)
	return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (i < cpenv->var_nb)
	{
		if (cpenv->envar[i] && ft_strncmp(cpenv->envar[i], key, ft_strlen(key)) == 0
			&& (cpenv->envar[i][len] == '='))
			return (cpenv->envar[i] + len + 1);
		i++;
	}
	return (NULL);
}
