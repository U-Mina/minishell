/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:17:26 by ewu               #+#    #+#             */
/*   Updated: 2024/12/18 19:09:32 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * modify ENV wrt
 * @export: ft_add_env_var (export var=val, '=' needed)
 * @cd: update PWD, OLDPWD
 * @unset: ft_del_env_var
 */

void	mod_cpenv_var(t_env *cpenv, char *key, char *val)
{}