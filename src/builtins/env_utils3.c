/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:45:08 by ewu               #+#    #+#             */
/*   Updated: 2025/01/21 15:19:39 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * get the value of env var
 */

//rename as *var_value()
char	*env_var_value(char **env, const char *key)
{
	int	i;
	int	len;

	if (!env || !key)
		return (NULL);
	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0
			&& (env[i][len] == '='))
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

void	del_val(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
		{
			gc_free(env[i]);
			env[i] = gc_strdup(key);
			//check: null check for env[i] or not?
			break ;
		}
		i++;
	}
}

void	mod_val(char **env, char *key, char *val)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '=' || env[i][len] == '\0'))
		{
			gc_free(env[i]);
			tmp = gc_strjoin(key, "=");
			env[i] = gc_strjoin(tmp, val);
			gc_free(tmp);
			return ;
		}
		i++;
	}
}
