/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 03:45:08 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 14:13:48 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// get the value of a env var
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
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '='))
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

// delete value of a env var (checking '=' sign)
void	del_val(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '='
			|| env[i][len] == '\0'))
		{
			gc_free(env[i]);
			env[i] = gc_strdup(key);
			if (env[i] == NULL)
				return ;
			break ;
		}
		i++;
	}
}

//change the value of an env var
void	mod_val(char **env, char *key, char *val)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && (env[i][len] == '='
			|| env[i][len] == '\0'))
		{
			gc_free(env[i]);
			tmp = gc_strjoin(key, "=");
			if (tmp == NULL)
				return ;
			env[i] = gc_strjoin(tmp, val);
			if (env[i] == NULL)
				return ;
			gc_free(tmp);
			return ;
		}
		i++;
	}
}
