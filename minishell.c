/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/12 16:36:55 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//include all allocated elements in gc_list (using gc_malloc and handle mallocated in other functions ex. ft_split)
//todo: char **envp need to be passed as para in main to get the env from sys 
int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_astnode	*ast_root;
	t_minishell	minishell;

	init_minishell(&minishell);
	while (1)
	{
		//Display a prompt when waiting for a new command
		input = readline("Prompt>");
		if(!input)
			break ;
		if (*input != '\0')
		{
			add_history(input);
			//Split into categorized tokens
			tokens = tokenizer(input);
			//free(input);//free at the end for all cases
			//check lexer
			print_tokens(tokens);
			//Create AST with hierarchized tokens
			ast_root = parse(tokens);
			//check parser
			print_ast(ast_root, 0);
			//execution
			//exec_ast(ast_root);
			//free allocated memory
			free_tokens(tokens);
			//pending of free ast
			// //execute the command saved into ast
			// //depending on the type of command: 
			// //1. search in files and exec the program
			// //2. create pipe, whatever
			// //3. exec a builtin function
			// exec(command);
		}
		free(input);
		rl_on_new_line();
	}
	term_minishell(&minishell, 0);
	//return (0); //already done in term_minshell!?
}

//disables the printing of Ctrl as ^ (ECHOCTL flag) and sets the Ctrl-D (4 is ASCII) to the value of EOF (for signal handling)
void	init_minishell(t_minishell	*minishell)
{
	struct termios term;

	init_signal_inter(minishell->sa, minishell->old_sa);
	tcgetattr(STDIN_FILENO, &(minishell->old_term));
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~ECHOCTL;
	term.c_cc[VEOF] = 4;
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

//restores the termios attributes and the signal actions to the original, and cleans all allocated items (gc_list) before exiting shell
void	term_minishell(t_minishell	*minishell, int rv)
{
	restore_signal(minishell->old_sa);
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->old_term));
	gc_clean();
	exit (rv); //return value???
}

//COMPROVATIONS
//check lexer
void	print_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_EOF)
	{
		printf("i: %i\ntype: %i\nvalue: %s\n\n", i, tokens[i].type, tokens[i].value);
		i++;
	}
}

//check parser
void	print_ast(t_astnode* ast_node, int level)
{
	int	i;
	int	j;

	i = 0;
	while(i++ < level)
		printf("	");
	if (ast_node->token->type == PIPE)
	{
		printf("%s (%i)\n", ast_node->token->value, ast_node->token->type);
		print_ast(ast_node->node_type.pipe->left, level + 1);
		print_ast(ast_node->node_type.pipe->right, level + 1);
	}
	else if (ast_node->token->type == REDIRECTION)
	{
		printf("%s (%i.%i): %s\n", ast_node->token->value, ast_node->token->type, ast_node->node_type.redirect->type, ast_node->node_type.redirect->left);
		print_ast(ast_node->node_type.redirect->right, level + 1);
	}
	else if (ast_node->token->type == COMMAND)
	{
		printf("%s (%i.%i):\n", ast_node->token->value, ast_node->token->type, ast_node->node_type.cmd->type);
		j = 1;
		while (j <= ast_node->node_type.cmd->arg_nb)
		{
			i = 0;
			while(i < level + 1)
			{
				printf("	");
				i++;
			}
			printf("arg %i: %s\n", j, ast_node->node_type.cmd->argv[j]);
			j++;
		}
	}
}

/** init and pass env to t_cmd */
void init_env(char **envp, t_cmd *cmd, int *exit_status)
{
	if (!envp[0])
	{
		cmd->env = create_env();
		if (cmd->env == NULL)
		{
			*exit_status = 1;
			exit(1);			
		}
	}
	else
	{
		cmd->env = cpy_env(envp);
		if (cmd->env == NULL)
		{
			*exit_status = 1;
			exit(1);			
		}
		change_shlvl_oldpwd(&cmd->env, "SHLVL", "OLDPWD");
	}
}
