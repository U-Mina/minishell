/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ipuig-pa <ipuig-pa@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:31:24 by ipuig-pa          #+#    #+#             */
/*   Updated: 2025/01/11 17:04:16 by ipuig-pa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//lexer or tokenizer (lexic analysis). Creates and returns an allocated array of token structures, that store the type of the token (to be further disambiguated according to the token context) and the value itself. 
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
		else if (*input == '|')
			tokens[current_token] = create_token(tokenizer, PIPE, "|");
		else if (*input == '$') // Pending of somehow handling $?
			tokens[current_token] = create_token(tokenizer, ENV_VAR, get_word(input));//extracts the name of the environmental variable, still pending of extending the value of the env_variable
		else if (*input == '>' || *input == '<')
			tokens[current_token] = create_token(tokenizer, REDIRECTION, get_redir(input));
		else if (*input == '\"' || *input == '\'')
			tokens[current_token] = create_token(tokenizer, QUOTE, get_quote(input, *input));
		else//if (ft_isalpha(*input))
			tokens[current_token] = create_token(tokenizer, WORD, get_word(input));
		//check that really all the cases which are not the previous are words (commands, arguments or textfiles)
		input = input + ft_strlen(tokens[current_token].value);
		current_token++;
	}
	printf("check pre\n");
	tokens[current_token] = create_token(tokenizer, TOKEN_EOF, NULL);
	printf("check final\n");
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

//creates a token and assigns the type and the value as set by the arguments. Returns the token.
t_token	create_token(t_tokenizer *tokenizer, t_tokentype type, char *value)
{
	t_token	token;

	if (tokenizer->count == tokenizer->capacity)
		grow_tokenizer(tokenizer);
	//error check???
	token.type = type;
	if (value)
		token.value = gc_strdup(value);
	else if (!value && type == TOKEN_EOF)
		token.value = NULL;
	//error check???
	//handle error when value is NULL(but it is not EOF) -> free previously allocated tokens and t
	// if (!value && type != TOKEN_EOF)
	// 	gc_malloc_error();
	tokenizer->count++;
	return (token);
}

//extracts a word (delimited by spaces) from the input and returns a pointer to the allocated string
char	*get_word(char *input)
{
	char	*word;
	int		word_len;

	word_len = 0;
	while (!ft_isspace(input[word_len]) && input[word_len] != '\0')
		word_len++;
	word = gc_malloc((word_len + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, input, word_len + 1);
	return (word);
}

//extracts a quote (delimited by quote_symbol (" or ')) from the input and returns a pointer to the allocated string. 
//Possibility to somehow join with get_word, managing with space as the required symbol?? have in mind the handling of unclosed quotes
char	*get_quote(char *input, char symbol)
{
	char	*quote;
	int		quote_len;

	quote_len = 0;
	quote_len++;
	while (input[quote_len] != symbol && input[quote_len] != '\0')
		quote_len++;
	quote_len++;
	//handle unclosed quotes here, as errors?!?!?
	// if (input[quote_len] != symbol)
	// 	handle_error();
	quote = gc_malloc((quote_len + 1) * sizeof(char));
	if (!quote)
		return (NULL);
	ft_strlcpy(quote, input, quote_len + 1);
	return (quote);
}

//extracts a redirection operator from the input and returns a pointer to the allocated string
char	*get_redir(char *input)
{
	char	*redir;
	int		redir_len;
	char	symbol;

	redir_len = 1;
	symbol = *input;
	if (input[redir_len] == symbol)
		redir_len++;
	redir = gc_malloc((redir_len + 1) * sizeof(char));
	//handle gc_malloc fail
	if (!redir)
		return (NULL);
	ft_strlcpy(redir, input, redir_len + 1);
	return (redir);
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

//include this function in libft??
//check if the passed character is an space
int	ft_isspace(char c)
{
	unsigned char	u_c;

	u_c = (unsigned char)c;
	if (u_c != c)
		return (0);
	if ((u_c >= 9 && u_c <= 13) || u_c == 32)
		return (1);
	return (0);
}
