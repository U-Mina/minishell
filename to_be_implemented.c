/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_be_implemented.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 12:54:03 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/09 13:06:04 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//expands the value of the env_variable (have in mind to pass it as an argument without the dollar sign before, or take it away in this function)
char	*expand_env_var(char *env_var)
{
	int		value_len;
	char	*value;

	//need to export from bash???
	value_len = ft_strlen(getenv(env_var));
	value = malloc((value_len + 1) * sizeof(char));
	if (!value)
		return (NULL);
	ft_strlcpy(value, getenv(env_var), value_len + 1);
	free(env_var);
	return (value);
}

////Previously working when inside the lexer.
//char	*get_env_var(char *input)
// {
// 	char	*env_var;
// 	int		value_len;
// 	char	*value;

// 	env_var = get_word(input + 1);
// 	if (!env_var)
// 		return (NULL);
// 	//need to export from bash???
// 	value_len = ft_strlen(getenv(env_var));
// 	value = malloc((value_len + 1) * sizeof(char));
// 	if (!value)
// 		return (NULL);
// 	ft_strlcpy(value, getenv(env_var), value_len + 1);
// 	free(env_var);
// 	return (value);
// }
