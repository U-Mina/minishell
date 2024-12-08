/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 12:38:49 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/08 11:11:54 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*input;

	//Display a prompt when waiting for a new command
	input = readline("Prompt>");
	//Have a working history 
	add_history(input);
	//parse command (have lexing into account?). Save the parsed command into structure?
	parsing(input);
	free(input);
	//execute the command saved into structure?
	//depending on the type of command: 
	//1. search in files and exec the program
	//2. create pipe, whatever
	//3. exec a builtin function
	exec(command);
}
