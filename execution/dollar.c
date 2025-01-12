/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 13:09:45 by ewu               #+#    #+#             */
/*   Updated: 2025/01/12 15:07:17 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * check '$'(dolloar_sign() == true)
 * stop at non-var_name position (var_name_checker()==true)
 * extrac and return 'var_name'
 * check_env to search for 'var' find_var ft'
 * return var or NULL
 */

bool var_name_check(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || ('0' <= c && c <= '9') || c == '_')
		return true;
	return false;
}

int	find_env_var(char **env, const char *key);

//arg == input after cmd == argv[1]
char *get_var_name(char *arg, size_t *pos)
{
	size_t i;
	char *name;

	i = *pos;
	if (arg[i] == '?')
		//get *exit_status
	
}