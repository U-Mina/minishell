/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:16:51 by ewu               #+#    #+#             */
/*   Updated: 2025/01/01 16:52:27 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//todo: -1/0 for builins to indicate fail/success
int ft_env(char  **env)
{
	int i;

	i = 0;
	if (env == NULL || env[0] == NULL)
		return (-1);
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != NULL) //ret ptr to '=' otherwise 'NULL'
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
