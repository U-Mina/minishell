/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:34:54 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 14:47:24 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	to_lower_str(char *str, char *low_cmd)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && i <= 7)
	{
		low_cmd[i] = ft_tolower(str[i]);
		i++;
	}
	low_cmd[i] = '\0';
}

int	exec_builtins(t_cmd *cmd, t_data *data)
{
	char	**args;
	char	low_cmd[7];

	args = cmd->argv;
	to_lower_str(args[0], low_cmd);
	if (ft_strncmp(low_cmd, "echo", 5) == 0)
		return (ft_echo(args, &data->exit_status), 0);
	else if (ft_strncmp(args[0], "cd", 3) == 0)
		return (ft_cd(args, &data->env, &data->exit_status), 0);
	else if (ft_strncmp(low_cmd, "pwd", 4) == 0)
		return (ft_pwd(&data->exit_status), 0);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		return (ft_export(&data->env, args, &data->exit_status), 0);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		return (ft_unset(args, &data->env, &data->exit_status), 0);
	else if (ft_strncmp(low_cmd, "env", 4) == 0)
		return (ft_env(data->env, &data->exit_status), 0);
	else if (ft_strncmp(args[0], "exit", 5) == 0)
		return (ft_exit(data, args), 0);
	return (data->exit_status = 1, -1);
}
