/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ewu <ewu@student.42heilbronn.de>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 13:01:04 by ewu               #+#    #+#             */
/*   Updated: 2025/01/17 16:52:01 by ewu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//disables the printing of Ctrl as ^ (ECHOCTL flag) and sets the Ctrl-D (4 is ASCII) to the value of EOF (for signal handling)
void	init_minishell(t_minishell	*minishell)
{
	struct termios	term;

	init_signal_inter(minishell->sa, minishell->old_sa);
	tcgetattr(STDIN_FILENO, &(minishell->old_term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	term.c_cc[VEOF] = 4;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

//this works for initialize the data in struct, such as **env, exit_status, and all other
//not sure about what data have been init already in parsing
//so this works also for checking and referrencing

/** init and pass env to t_cmd */
void	init_data(char **envp, t_data *data, int *exit_status)
{
	data->exit_status = exit_status;
	data->fd[0] = STDIN_FILENO;
	data->fd[1] = STDOUT_FILENO;
	//^^ being set in parse_cmd alreadt
	if (!envp[0])
	{
		data->env = create_env();
		if (data->env == NULL)
		{
			*(data->exit_status) = 1;
			exit (1);
		}
	}
	else
	{
		data->env = cpy_env(envp);
		if (data->env == NULL)
		{
			*(data->exit_status) = 1;
			exit (1);
		}
		change_shlvl_oldpwd(&data->env, "SHLVL", "OLDPWD");
	}
}

//check: try bad input
//debug: not sure what para to pass
void *init_cmd_node(t_cmd *cmd_node)
{
	cmd_node->arg_nb = 0;
	cmd_node->argv = NULL;
	cmd_node->path = NULL;
}

void *init_redir_node(t_redir *redir_node)
{
	redir_node->left = NULL;
	redir_node->right = NULL;
}

void *init_pip_node(t_pipe *pipe_node)
{
	pipe_node->left = NULL;
	pipe_node->right = NULL;
}
