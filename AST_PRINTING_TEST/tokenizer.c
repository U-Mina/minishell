/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 10:26:27 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/14 14:59:53 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer or tokenizer (lexic analysis). Creates and returns an allocated array of token structures, that store the type of the token (to be further disambiguated according to the token context) and the value itself
t_token	*tokenizer(char *input)
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
			create_token(tokenizer, input);
		input = input + tokens[current_token].i_len;
		current_token++;
	}
	create_token(tokenizer, input);
	return (tokens);
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
void	create_token(t_tokenizer *tokenizer, char *input)
{
	if (tokenizer->count == tokenizer->capacity)
		grow_tokenizer(tokenizer);
	//error check, if !grow_tokenizer(tokenizer)???
	if (*input == '\0')
		make_eof_token(&tokenizer->tokens[tokenizer->count]);
	else if (*input == '|')
		make_pipe_token(&tokenizer->tokens[tokenizer->count]);
	else if (*input == '>' || *input == '<')
		make_redir_token(&tokenizer->tokens[tokenizer->count], input);
	else if (*input == '$')
		make_env_var_token(&tokenizer->tokens[tokenizer->count], input);
	else if (*input == '\"' || *input == '\'')
		make_quote_token(&tokenizer->tokens[tokenizer->count], input, *input);
	else
		make_word_token(&tokenizer->tokens[tokenizer->count], input);
	tokenizer->count++;
}

//to use after tokens have been used. Frees each allocated value in the token structure array and frees the whole array
void	free_tokens(t_token *tokens)
{
	int	i;

	i = 0;
	while (tokens[i].type != TOKEN_EOF)
	{
		if (tokens[i].type != PIPE)
			gc_free(tokens[i].value);
		i++;
	}
	gc_free(tokens);
}