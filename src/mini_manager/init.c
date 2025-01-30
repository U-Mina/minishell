/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:01:04 by ewu               #+#    #+#             */
/*   Updated: 2025/01/30 12:49:44 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//disables the printing of Ctrl as ^ (ECHOCTL flag) and
//sets the Ctrl-D (4 is ASCII) to the value of EOF (for signal handling)
static void	init_minishell(t_minishell	*minishell, int ac, char **av)
{
	(void)ac;
	(void)av;
	init_signal_inter(minishell->sa, minishell->old_sa);
	tcgetattr(STDIN_FILENO, &(minishell->old_term));
	tcgetattr(STDIN_FILENO, &(minishell->term));
	minishell->term.c_lflag &= ~ECHOCTL;
	minishell->term.c_cc[VEOF] = 4;
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->term));
}

//creates a new env if needed
static void	set_env(char **envp, t_data *data)
{
	if (!envp[0])
	{
		data->env = create_env();
		if (data->env == NULL)
		{
			data->exit_status = 1;
			exit (1);
		}
	}
	else
	{
		data->env = cpy_env(envp);
		if (data->env == NULL)
		{
			data->exit_status = 1;
			exit (1);
		}
		change_shlvl_oldpwd(&data->env, "SHLVL", "OLDPWD");
	}
}

//initializes the data struct, such as **env, exit_status, and fd
void	init(char **envp, t_data *data, int ac, char **av)
{
	init_minishell(&data->minishell, ac, av);
	data->exit_status = 0;
	data->child_status = 0;
	data->o_fd[0] = dup(STDIN_FILENO);
	data->o_fd[1] = dup(STDOUT_FILENO);
	data->fd[0] = STDIN_FILENO;
	data->fd[1] = STDOUT_FILENO;
	data->heredoc_fd = 1;
	data->malloc_err = false;
	set_env(envp, data);
	data->tokens = NULL;
	data->ast_root = NULL;
}
