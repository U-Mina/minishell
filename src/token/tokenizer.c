/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:26:27 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/29 15:47:40 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//initiates the tokenizer structure, that will hold
//the array of tokens and 
//some parameters regarding its capacity
static t_tokenizer	*init_tokenizer(void)
{
	t_tokenizer	*tokenizer;

	tokenizer = gc_malloc(sizeof(t_tokenizer));
	if (!tokenizer)
		return (NULL);
	tokenizer->capacity = 20;
	tokenizer->grow = 20;
	tokenizer->count = 0;
	tokenizer->tokens = gc_malloc(tokenizer->capacity * sizeof(t_token));
	if (!tokenizer->tokens)
		return (NULL);
	return (tokenizer);
}

//reallocates space for more tokens in the tokenizer,
//according to the factor "tokenizer->grow"
static int	grow_tokenizer(t_tokenizer *tokenizer)
{
	int		new_capacity;
	t_token	*new_tokens;

	new_capacity = tokenizer->capacity + tokenizer->grow;
	new_tokens = gc_malloc(new_capacity * sizeof(t_token));
	if (!new_tokens)
		return (0);
	ft_memcpy(new_tokens, tokenizer->tokens, tokenizer->capacity \
													* sizeof(t_token));
	gc_free(tokenizer->tokens);
	tokenizer->tokens = new_tokens;
	tokenizer->capacity = new_capacity;
	return (1);
}

//creates and allocates a token in the tokenizer and
//assigns the type, the value, and the len according to the input.
static int	create_token(t_tokenizer *tokenizer, char *input)
{
	t_token	*token;
	int		success;

	token = &(tokenizer->tokens[tokenizer->count]);
	if (tokenizer->count == tokenizer->capacity)
	{
		if (!grow_tokenizer(tokenizer))
			return (0);
	}
	if (*input == '\0')
		success = make_eof_token(token);
	else if (*input == '|')
		success = make_pipe_token(token);
	else if (*input == '>' || *input == '<')
		success = make_redir_token(token, input);
	else
		success = make_word_token(token, input);
	if (!success)
		return (0);
	tokenizer->count++;
	return (1);
}

//lexer or tokenizer (lexic analysis)
//Creates and returns an allocated array of token structures, 
//store the type of the token (to be further disambiguated according to context)
//and the value itself
int	tokenizer(char *input, t_data *data)
{
	int			current_token;
	t_tokenizer	*tokenizer;

	tokenizer = init_tokenizer();
	if (!tokenizer)
		return (set_malloc_error(data), 0);
	current_token = 0;
	while (*input != '\0')
	{
		while (ft_isspace(*input))
			input++;
		if (*input == '\0')
			break ;
		else
		{
			if (!create_token(tokenizer, input))
				return (0);
		}
		input = input + ft_strlen(tokenizer->tokens[current_token].value);
		current_token++;
	}
	if (!create_token(tokenizer, input))
		return (set_malloc_error(data), 0);
	data->tokens = tokenizer->tokens;
	return (1);
}
