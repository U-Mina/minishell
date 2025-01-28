/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:01:04 by ewu               #+#    #+#             */
/*   Updated: 2025/01/28 19:57:41 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//disables the printing of Ctrl as ^ (ECHOCTL flag) and sets the Ctrl-D (4 is ASCII) to the value of EOF (for signal handling)
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

//this works for initialize the data in struct, such as **env, exit_status, and all other
//not sure about what data have been init already in parsing
//so this works also for checking and referrencing

/** init and pass env to t_cmd */
void	init(char **envp, t_data *data, int ac, char **av)
{
	init_minishell(&data->minishell, ac, av);
	data->exit_status = 0;
	data->o_fd[0] = dup(STDIN_FILENO);
	data->o_fd[1] = dup(STDOUT_FILENO);
	data->fd[0] = STDIN_FILENO;
	data->fd[1] = STDOUT_FILENO;
	data->heredoc_fd = 1;
	//^^ being set in parse_cmd already
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

void	reset_data(t_data *data)
{
	data->heredoc_fd = -1;
	dup2(data->o_fd[0], STDIN_FILENO);
	data->fd[0] = STDIN_FILENO;
	dup2(data->o_fd[1], STDOUT_FILENO);
	data->fd[1] = STDOUT_FILENO;
	if (data->ast_root)
		free_ast(data->ast_root);
	if (data->tokens)
		gc_free(data->tokens);
}

void	check_signal(t_data *data)
{
	if (g_signal == SIGINT)
	{
		data->exit_status = 1;
		g_signal = 0;
	}
}
