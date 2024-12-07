/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2024/12/07 17:13:07 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


typedef enum e_tokentype
{
	COMMAND,
	ARGUMENT,
	REDIRECTION,
	PIPE,
	ENV_VAR,
	QUOTE,
	FILENAME
}	t_tokentype

typedef	struct s_tokens
{
	t_tokentype	type;
	char		*value;
}			t_tokens

//parser (syntactic analysis)
void	parse (char *input)
{
	
}


//lexer or tokenizer (lexic analysis)
t_tokens*	tokenizer(char *input)
{
	int			token_num;
	int			current_token;
	t_tokens	*tokens;
	int			i;

	token_num = get_token_num(input);
	tokens = (t_tokens *)malloc((token_num + 1) * sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	current_token = 0;
	//confirm that the readline command give the line null-terminated
	//PROBLEM!: use again ft_split here to take each "word" and be easier classifying -> be aware of quotes, it will split it!!!! (in fact, they will be split in the token counter)
	while (input[i] != '\0') //&& current_token < token_num) (needed for some reason?)
	{
		//in this part, fill the tokens[] array, checking its type and setting its value
		
		//check the name of the functions is_alpha, etc. from the library
		if (input[i] = is_alpha())
		tokens[current_token] = 
		current_token++;
	}
	return (tokens);
}


int	get_token_num(char *input)
{
	char	**split;
	int		token_num;

	token_num = 0;
	split = ft_split(input, ' ');
	while (split[token_num] != NULL)
	{
		free(split[token_num]);
		token_num++;
	}
	free(split);
	return (token_num);
}



if (is_command())
	tokens[i] = add_token(COMMAND, )
else if (is_pipe())

is_command()

add_token(t_tokentype tokentype, char *str)
{
	
}