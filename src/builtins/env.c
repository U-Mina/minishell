/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:16:51 by ewu               #+#    #+#             */
/*   Updated: 2025/01/19 16:09:23 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//idea: **env == **cpenv, with shlvl+1 and OLDPWD changed
int	ft_env(char **env, int *exit_status)
{
	int	i;

	i = 0;
	if (env == NULL || env[0] == NULL)
		return (-1);
	while (env[i])
	{
		if (ft_strchr(env[i], '=') != NULL) 
		//ret ptr to '=' otherwise 'NULL'
			printf("%s\n", env[i]);
		i++;
	}
	*exit_status = 0;
	return (0);
}
