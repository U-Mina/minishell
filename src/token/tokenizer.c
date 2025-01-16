/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:26:27 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/16 12:11:52 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer or tokenizer (lexic analysis). Creates and returns an allocated array of token structures, that store the type of the token (to be further disambiguated according to the token context) and the value itself
t_token	*tokenizer(char *input, int *exit_status)
{
	int			current_token;
	t_token		*tokens;
	t_tokenizer	*tokenizer;

	tokenizer = init_tokenizer();
	tokens = tokenizer->tokens;
	current_token = 0;
	while (*input != '\0')
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		else
			create_token(tokenizer, input, exit_status);
		input = input + tokens[current_token].i_len;
		current_token++;
	}
	create_token(tokenizer, input, exit_status);
	return (tokens); // or if data is passed for exit status, have here data->tokens = tokens; and make the function void and in the main, the data->tokens will be passed to the parsing part
}

t_tokenizer	*init_tokenizer(void)
{
	t_tokenizer	*tokenizer;

	tokenizer = gc_malloc(sizeof(t_tokenizer));
	// if (!tokenizer)
	// 	return (handle_error(gc_list));
	tokenizer->capacity = 20;
	tokenizer->grow = 20;
	tokenizer->count = 0;
	tokenizer->tokens = gc_malloc(tokenizer->capacity * sizeof(t_token));
	// if (!tokenizer->tokens)
	// 	return (handle_error(gc_list));
	return (tokenizer);
}

int	grow_tokenizer(t_tokenizer *tokenizer)
{
	int		new_capacity;
	t_token	*new_tokens;

	new_capacity = tokenizer->capacity + tokenizer->grow;
	new_tokens = gc_malloc(new_capacity * sizeof(t_token));
	// if (!new_tokens)
	// {
	// 	handle_error(gc_list);
	// 	return (1);
	// }
	ft_memcpy(new_tokens, tokenizer->tokens, tokenizer->capacity * sizeof(t_token));
	gc_free(tokenizer->tokens);
	tokenizer->tokens = new_tokens;
	tokenizer->capacity = new_capacity;
	return (1);
}

//creates and allocates a token in the tokenizer and assigns the type, the value, and the len according to the input.
void	create_token(t_tokenizer *tokenizer, char *input, int *ex_st)
{
	t_token	*token;

	token = &(tokenizer->tokens[tokenizer->count]);
	if (tokenizer->count == tokenizer->capacity)
		grow_tokenizer(tokenizer);
	//error check, if !grow_tokenizer(tokenizer)???
	if (*input == '\0')
		make_eof_token(token);
	else if (*input == '|')
		make_pipe_token(token);
	else if (*input == '>' || *input == '<')
		make_redir_token(token, input);
//	else if (*input == '$')
//		make_env_var_token(token, input, ex_st);
	else if (*input == '\"' || *input == '\'')
		make_quote_token(token, input, ex_st);
	else
		make_word_token(token, input, ex_st);
	tokenizer->count++;
}
