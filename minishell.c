/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/09 12:40:42 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;
	int		i;

	// //Add signal handling
	while (1)
	{
		//Display a prompt when waiting for a new command
		input = readline("Prompt>");
		//Have a working history 
		add_history(input);
		//Split into categorized tokens
		tokens = tokenizer(input);
		//check lexer
		i = 0;
		while (tokens[i].type != TOKEN_EOF)
		{
			printf("i: %i\ntype: %i\nvalue: %s\n\n", i, tokens[i].type, tokens[i].value);
			i++;
		}
		free(input);
		// ast = parse(tokens);
		free_tokens(&tokens);
		// //execute the command saved into ast
		// //depending on the type of command: 
		// //1. search in files and exec the program
		// //2. create pipe, whatever
		// //3. exec a builtin function
		// exec(command);
	}
	return (0);
}

