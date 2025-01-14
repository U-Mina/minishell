/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:01:04 by ewu               #+#    #+#             */
/*   Updated: 2025/01/14 14:33:41 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//this works for initialize the data in struct, such as **env, exit_status, and all other
//not sure about what data have been init already in parsing
//so this works also for checking and referrencing


/** init and pass env to t_cmd */
void init_data(char **envp, t_data *data)
{
	data->exit_status = 0;
	//^^ being set in parse_cmd alreadt
	if (!envp[0])
	{
		data->env = create_env();
		if (data->env == NULL)
		{
			data->exit_status = 1;
			exit(1);			
		}
	}
	else
	{
		data->env = cpy_env(envp);
		if (data->env == NULL)
		{
			data->exit_status = 1;
			exit(1);			
		}
		change_shlvl_oldpwd(&data->env, "SHLVL", "OLDPWD");
	}
}
