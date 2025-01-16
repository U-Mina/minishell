/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 11:23:41 by ewu               #+#    #+#             */
/*   Updated: 2025/01/15 11:40:48 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool check_flag(char *arg)
{
	if (!*arg)
		return (false);
	if (*arg == '-' && *(arg + 1))
	{
		arg++;
		while (*arg == 'n')
			arg++;
	}
	if (*arg)
		return (false);
	return (true);
}

void ft_echo(char **args, int* exit_status)
{
	bool flag;
	
	flag = false;
	args++;
	while (*args && check_flag(*args))
	{
		flag = true;
		args++;
	}
	while (*args)
	{
		printf("%s", *args++);
		if (*args)
		printf(" ");
	}
	if (flag == false)
		printf("\n");
	*exit_status = 0;
}
